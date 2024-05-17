#include "../../minilibx-linux/mlx.h"
#include "../../minilibx-linux/mlx_int.h"
#include "../../libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define PI 3.1415926535
#define FOV 110
#define FOV_RAD (FOV * PI / 180)
#define PLANE_FOV tan(FOV_RAD / 2)
#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 400

#define PLAYER_STEP_SIZE 0.1

int g_grid[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct s_fvector
{
    float x;
    float y;
} t_fvector;

typedef struct s_dvector
{
    double x;
    double y;
} t_dvector;

typedef struct s_ivector
{
    int x;
    int y;
} t_ivector;

typedef struct s_player
{
    t_dvector pos;
    double relative_dir_angle;

    t_dvector dir;
    t_dvector plane;

    t_dvector movement;
} t_player;

typedef struct s_grid
{
    int **content;
    int width;
    int height;
    int size;
} t_grid;

typedef struct t_dda
{
    double dist;
    char orientation;
} t_dda;

typedef struct s_ray
{
    t_ivector grid_pos;
    t_dvector true_pos;
    t_dvector dir;

    t_dvector delta_dist;
    t_dvector side_dist;
    t_ivector step_direction;
} t_ray;

typedef struct s_raycast
{
    double camera_x;
    double perp_wall_dist;
    t_ray ray;
} t_raycast;

typedef struct s_cub3d
{
    void *mlx;
    void *mlx_win;
    t_grid grid;
    t_player player;
} t_cub3d;

double to_rad(int degrees)
{
    return (degrees * PI / 180);
}

bool is_wall_detected(const t_grid *grid, const t_ray *ray)
{
    return (grid->content[ray->grid_pos.y][ray->grid_pos.x] == 1);
}

double process_wall_dist(char last_side_tested, const t_ray *ray)
{
    if (last_side_tested == 'x')
        return ((ray->grid_pos.x - ray->true_pos.x + (1 - ray->step_direction.x) / 2) / ray->dir.x);
    else
        return ((ray->grid_pos.y - ray->true_pos.y + (1 - ray->step_direction.y) / 2) / ray->dir.y);
}

char process_wall_orientation(const t_player *player, char last_side_tested)
{
    if (last_side_tested == 'x')
    {
        if (player->dir.x > 0)
            return 'E'; // East
        else
            return 'W'; // West
    }
    else
    {
        if (player->dir.y > 0)
            return 'S'; // South
        else
            return 'N'; // North
    }
}

void get_wall_config_dda(const t_player *player, const t_grid *grid, t_ray *ray, t_dda *wall_config)
{
    bool hit = false;
    char last_side_tested;

    while (!hit)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->grid_pos.x += ray->step_direction.x;
            last_side_tested = 'x';
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->grid_pos.y += ray->step_direction.y;
            last_side_tested = 'y';
        }
        hit = is_wall_detected(grid, ray);
    }
    wall_config->dist = process_wall_dist(last_side_tested, ray);
    wall_config->orientation = process_wall_orientation(player, last_side_tested);
}

void init_ray(const double camera_x, t_player *player, t_ray *ray)
{
    ray->true_pos.x = player->pos.x;
    ray->true_pos.y = player->pos.y;
    ray->grid_pos.x = (int)player->pos.x;
    ray->grid_pos.y = (int)player->pos.y;

    ray->dir.x = player->dir.x + player->plane.x * camera_x;
    ray->dir.y = player->dir.y + player->plane.y * camera_x;
}

void get_ray_config_dda(t_ray *ray)
{
    ray->delta_dist.x = fabs(1 / ray->dir.x);
    ray->delta_dist.y = fabs(1 / ray->dir.y);
    if (ray->dir.x < 0)
    {
        ray->step_direction.x = -1;
        ray->side_dist.x = (ray->true_pos.x - ray->grid_pos.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step_direction.x = 1;
        ray->side_dist.x = (ray->grid_pos.x + 1.0 - ray->true_pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step_direction.y = -1;
        ray->side_dist.y = (ray->true_pos.y - ray->grid_pos.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step_direction.y = 1;
        ray->side_dist.y = (ray->grid_pos.y + 1.0 - ray->true_pos.y) * ray->delta_dist.y;
    }
}

int color_to_display(char wall_orientation)
{
    if (wall_orientation == 'N')
        return 0xFF0000; // Red
    else if (wall_orientation == 'S')
        return 0x00FF00; // Green
    else if (wall_orientation == 'E')
        return 0x0000FF; // Blue
    return 0xFFFF00; // Yellow
}

void add_pixels_col_to_img(t_cub3d *data, const int pixel_x, const t_dda *wall_config)
{
    int displayed_height;
    int pixel_y;
    int color;

    color = color_to_display(wall_config->orientation);
    displayed_height = (int)(SCREEN_HEIGHT / wall_config->dist);
    pixel_y = (SCREEN_HEIGHT - displayed_height) / 2;

    while (pixel_y < (SCREEN_HEIGHT + displayed_height) / 2)
    {
        mlx_pixel_put(data->mlx, data->mlx_win, pixel_x, pixel_y, color);
        pixel_y++;
    }
}

void create_raycast_img(t_cub3d *data)
{
    t_ray ray;
    t_player *player = &(data->player);
    t_dda wall_ray;
    double camera_x;

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        init_ray(camera_x, player, &ray);
        get_ray_config_dda(&ray);
        get_wall_config_dda(&(data->player), &(data->grid), &ray, &wall_ray);
        add_pixels_col_to_img(data, x, &wall_ray);
    }
}

bool is_valid_move(t_grid *grid, double new_x, double new_y)
{
    int grid_x = (int)new_x;
    int grid_y = (int)new_y;

    if (grid_x < 0 || grid_x >= grid->width || grid_y < 0 || grid_y >= grid->height)
    {
        return false; // Out of bounds
    }

    if (grid->content[grid_y][grid_x] == 1)
    {
        return false; // Collision with wall
    }

    return true;
}

void modif_player_pos(int key, t_player *player, t_grid *grid)
{
    double new_x = player->pos.x;
    double new_y = player->pos.y;
    double movement_perp_x = player->movement.y;
    double movement_perp_y = -player->movement.x;

    if (key == XK_w)
    {
        new_x += player->movement.x;
        new_y += player->movement.y;
    }
    else if (key == XK_s)
    {
        new_x -= player->movement.x;
        new_y -= player->movement.y;
    }
    else if (key == XK_a)
    {
        new_x += movement_perp_x;
        new_y += movement_perp_y;
    }
    else if (key == XK_d)
    {
        new_x -= movement_perp_x;
        new_y -= movement_perp_y;
    }

    if (is_valid_move(grid, new_x, new_y))
    {
        player->pos.x = new_x;
        player->pos.y = new_y;
    }
}

void modif_player_movement(t_player *player)
{
    player->movement.x = cos(player->relative_dir_angle) * PLAYER_STEP_SIZE;
    player->movement.y = sin(player->relative_dir_angle) * PLAYER_STEP_SIZE;
}

void modif_player_dir(int key, t_player *player)
{
    if (key == XK_Left)
    {
        player->relative_dir_angle -= 0.1;
        if (player->relative_dir_angle < 0)
            player->relative_dir_angle += 2 * PI;
    }
    if (key == XK_Right)
    {
        player->relative_dir_angle += 0.1;
        if (player->relative_dir_angle > 2 * PI)
            player->relative_dir_angle -= 2 * PI;
    }

    player->dir.x = cos(player->relative_dir_angle);
    player->dir.y = sin(player->relative_dir_angle);
    player->plane.x = -player->dir.y * PLANE_FOV;
    player->plane.y = player->dir.x * PLANE_FOV;
}

int modif_player(int key, t_cub3d *data)
{
    mlx_clear_window(data->mlx, data->mlx_win);
    if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
        modif_player_pos(key, &(data->player), &(data->grid));
    if (key == XK_Left || key == XK_Right)
    {
        modif_player_dir(key, &(data->player));
        modif_player_movement(&(data->player));
    }
    create_raycast_img(data);
    return (0);
}

void init_player(t_cub3d const *data, t_player *player)
{
    (void)data;
    player->pos.x = 1.1; // a la position 1 on voit au travers du mur
    player->pos.y = 1.1;

    player->relative_dir_angle = to_rad(45);
    player->dir.x = cos(player->relative_dir_angle);
    player->dir.y = sin(player->relative_dir_angle);
    player->movement.x = player->dir.x * PLAYER_STEP_SIZE;
    player->movement.y = player->dir.y * PLAYER_STEP_SIZE;

    player->plane.x = -player->dir.y * PLANE_FOV;
    player->plane.y = player->dir.x * PLANE_FOV;
}

void init_grid(t_grid *grid)
{
    grid->content = (int **)malloc(8 * sizeof(int *));
    for (int i = 0; i < 8; i++)
    {
        grid->content[i] = (int *)malloc(8 * sizeof(int));
    }

    for (int k = 0; k < 8; k++)
    {
        for (int l = 0; l < 8; l++)
        {
            grid->content[k][l] = g_grid[k][l];
        }
    }

    grid->height = 8;
    grid->width = 8;
    grid->size = 64;
}

int main()
{
    t_cub3d data;
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    init_player(&data, &(data.player));
    init_grid(&(data.grid));
    // memset(&data.ray, 0, sizeof(t_ray));
    create_raycast_img(&data);
    mlx_hook(data.mlx_win, 2, 1L << 0, modif_player, &data);
    mlx_loop(data.mlx);
    return 0;
}
