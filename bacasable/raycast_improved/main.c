#include "../../minilibx-linux/mlx.h"
#include "../../minilibx-linux/mlx_int.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

# define FOV 66
# define FOV_RAD (FOV * M_PI/180)

char g_grid[8][8] = {
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

typedef struct s_ray
{
    int r;
    int mx;
    int my;
    int mp;
    int dof;
    float rx;
    float ry;
    float ra;
    float xo;
    float yo;
} t_ray;


typedef struct s_player
{
    t_dvector pos;  //(grid)
    t_dvector dir;  //(player.pos)
    t_dvector plane; //(player_dir)
} t_player;

//grid = 01
// map = grid * 64
typedef struct s_grid
{
    char **content; //remplacer par char**
    int width; //limiter la taille de la grille a 1000 col
    int height;  //limiter la taille de la grille a 1000 lignes
    int size; // max width * size attention a ce que cela rentre dans un int
} t_grid;

// typedef struct s_raycast
// {
//     double camera_x;
//     t_dvector raydir; // (grid)
//     t_player *player // (grid)
//     t_dvector side_dist;
//     t_dvector delta_dist;
//     double perp_wall_dist;
//     int step_x;
//     int step_y;
//     int hit;
//     int side;
// } t_raycast;

typedef struct s_cub3d
{
    void *mlx;
    void *mlx_win;
    t_ray ray;
    t_grid grid; //redit avec player pos ?
    t_player player;
    // t_raycast raycast;
} t_cub3d;

#define W 122
#define A 113
#define S 115
#define D 100
#define PI 3.1415926535

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(mlx, win, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// void	draw_screen(t_cub3d data)
// {
	
// }

void draw_ray_dir(t_cub3d data)
{
	
    double posX = data.playerX / data.grid.size; // Position du joueur en coordonnées carte
    double posY = data.playerY / data.grid.size;
    printf("pX %f PY %f\n", posX, posY);
	double dirX = cos(data.playerAngle);
    double dirY = sin(data.playerAngle);
	printf(" dirX %f, dirY %f\n", dirX, dirY);
    double planeX = 0.66 * -dirY; // Plan de la caméra pour créer le FOV
    double planeY = 0.66 * dirX;
	printf(" planeX %f, planeY %f\n", planeX, planeY);

    // Afficher la direction du joueur
    // double dirX_map = posX + dirX; // 5 est une constante pour la longueur de la ligne directionnelle
    // double dirY_map = posY + dirY;
    
	printf("ecran start X %f ecran start Y %f\n", posX + dirX + planeX, posY + dirY + planeY);
    printf("ecran end X %f ecran end Y %f\n", posX + dirX - planeX, posY + dirY - planeY);
	for (int x = 0; x < 800; x++)
    {
        double cameraX = 2 * x / (double)800 - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(data.grid.size/ rayDirX);
        double deltaDistY = fabs(data.grid.size/ rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (data.map[mapY][mapX] > 0)
			{
                hit = 1;
				//printf("HIT\n");
			}
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else 
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(600 / perpWallDist);

        // draw the pixels of the stripe as a vertical line
        for(int y = (600 - lineHeight) / 2; y < (600 + lineHeight) / 2; y++)
            mlx_pixel_put(data.mlx, data.mlx_win, x, y, 0xFFFFFF); // Assume 0xFFFFFF is the color of the wall
		 
    }
}

void draw_player(t_cub3d data)
{
    int square_size = 10;
    int half_size = square_size / 2;
    int x_start = data.playerX - half_size;
    int y_start = data.playerY - half_size;
    int x_end = data.playerX + half_size;
    int y_end = data.playerY + half_size;

    for (int y = y_start; y <= y_end; y++)
    {
        for (int x = x_start; x <= x_end; x++)
        {
            mlx_pixel_put(data.mlx, data.mlx_win, x, y, 0xFFFFFF); // Dessiner le carré en blanc
        }
    }
}


void draw_map(t_cub3d data)
{
    int x;
    int y;
    int i; // Variable pour la boucle interne horizontale
    int j; // Variable pour la boucle interne verticale

    y = 0;
    while (y < 8)
    {
        x = 0;
        while (x < 8)
        {
            if (data.map[y][x] == 1)
            {
                j = 0;
                while (j < data.grid.size) // Boucle pour la hauteur du carré
                {
                    i = 0;
                    while (i < data.grid.size) // Boucle pour la largeur du carré
                    {
                        mlx_pixel_put(data.mlx, data.mlx_win, x * data.grid.size+ i, y * data.grid.size+ j, 0x0000FF);
                        i++;
                    }
                    j++;
                }
            }
            x++;
        }
        y++;
    }

    // Dessiner les lignes de la grille
    for (int gridY = 0; gridY <= 8; gridY++) // Lignes horizontales
    {
        for (int pixel = 0; pixel < 8 * data.grid.size; pixel++) // 8 cellules * data.grid.sizepixels par cellule
        {
            mlx_pixel_put(data.mlx, data.mlx_win, pixel, gridY * data.grid.size, 0x0000FF); // Ligne bleue
        }
    }
    for (int gridX = 0; gridX <= 8; gridX++) // Lignes verticales
    {
        for (int pixel = 0; pixel < 8 * data.grid.size; pixel++)
        {
            mlx_pixel_put(data.mlx, data.mlx_win, gridX * data.grid.size, pixel, 0x0000FF); // Ligne bleue
        }
    }
}

int buttons(int key, t_cub3d *data)
{
    mlx_clear_window(data->mlx, data->mlx_win);

    if (key == XK_w)
    {
        data->playerX += data->deltaX;
        data->playerY += data->deltaY;
    }
    if (key == XK_a)
    {
        data->playerAngle -= 0.1;
        if (data->playerAngle < 0)
            data->playerAngle += 2 * PI;
        data->deltaX = cos(data->playerAngle) * 5;
        data->deltaY = sin(data->playerAngle) * 5;
    }
    if (key == XK_s)
    {
        data->playerX -= data->deltaX;
        data->playerY -= data->deltaY;
    }
    if (key == XK_d)
    {
        data->playerAngle += 0.1;
        if (data->playerAngle > 2 * PI)
            data->playerAngle -= 2 * PI;
        data->deltaX = cos(data->playerAngle) * 5;
        data->deltaY = sin(data->playerAngle) * 5;
    }
	draw_ray_dir(*data);
    // draw_map(*data);
    // draw_player(*data);
    return (0);
}

void init_player(t_cub3d const *data, t_player *player)
{
    player->pos.x = data->grid.size; //cela dependra de pos du joueur sur la grid (on le place sur grid_x = 1 pour le mom)
    player->pos.y = data->grid.size; //cela dependra de pos du joueur sur la grid (on le place sur grid_y = 1 pour le mom)
    player->dir.x = cos(to_rad(45)); //cela dependra de la dir du joueur sur la grid (on part sur un angle a 45deg) 
    player->dir.y = sin(to_rad(45)); //cela dependra de la dir du joueur sur la grid (on part sur un angle a 45deg) 
    player->plane.x = player->dir.x + tan(FOV_RAD/2); //par rapport a playerdir
    player->plane.y = 0; //inutile
}

//void move_player(t_cub3d const *data, t_player *player); //hook
// {
//     //bouger la pos si certaines touches sont appuyees
//     //bouger la dir si certaines touches sont appuyees (pas de modif si c'est la pos qui bouge)
//     //remettre a jour les valeurs de plane
// }

void init_grid(t_cub3d const *data, t_grid *grid)
{
    grid->content = g_grid; //mettre la grille parsee dnas cette var
    grid->width = ft_strlen(g_grid[0]); //
    grid->height = 8; //
}
double to_rad(int degrees)
{
    return(degrees * M_PI/180);
}

int main()
{
    t_cub3d data;
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 800, 600, "Raycaster");
    data.grid.size= 64;

    //init player 
    init_player(&data, &(data.player));
    init_grid(&data, &(data.player));
    memset(&data.ray, 0, sizeof(t_ray));

    // Boucle pour garder la fenêtre ouverte
    // draw_map(data);
    // draw_player(data);
	draw_ray_dir(data);
    mlx_hook(data.mlx_win, 2, 1L << 0, buttons, &data);
    mlx_loop(data.mlx);
    return (0);
}
