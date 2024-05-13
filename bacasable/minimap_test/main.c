#include "../../robin_cub3d/mlx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 20
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define PLAYER_SIZE 4
#define RAY_COLOR 0xFF0000 // Red
#define PLAYER_COLOR 0x00FF00 // Green
#define SCREEN_COLOR 0x0000FF // Blue


typedef struct s_player {
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_minimap {
    t_player    *player;
    int (*map)[MAP_WIDTH];
    void        *mlx_ptr;
    void        *win_ptr;
} t_minimap;

void draw_player(void *mlx_ptr, void *win_ptr, t_player *player) {
    mlx_pixel_put(mlx_ptr, win_ptr, player->x, player->y, PLAYER_COLOR);
}

// void draw_rays(void *mlx_ptr, void *win_ptr, t_player *player) {
//     double ray_angle;
//     int end_x, end_y;
//     for (ray_angle = player->angle - M_PI / 6; ray_angle <= player->angle + M_PI / 6; ray_angle += M_PI / (3 * SCREEN_WIDTH)) {
//         end_x = player->x + SCREEN_WIDTH * cos(ray_angle);
//         end_y = player->y + SCREEN_WIDTH * sin(ray_angle);
//         mlx_line_put(mlx_ptr, win_ptr, player->x, player->y, end_x, end_y, RAY_COLOR);
//     }
// }

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy, err, e2;

    if (x0 < x1) sx = 1; else sx = -1;
    if (y0 < y1) sy = 1; else sy = -1;

    err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void draw_rays(void *mlx_ptr, void *win_ptr, t_player *player, int (*map)[MAP_WIDTH]) {
    double ray_angle;
    // int end_x, end_y;
    int map_x, map_y;
    double step_x, step_y;
    double delta_dist_x, delta_dist_y;
    double side_dist_x, side_dist_y;
    double perp_wall_dist;
    int hit = 0;
    int side;

    for (ray_angle = player->angle - M_PI / 6; ray_angle <= player->angle + M_PI / 6; ray_angle += M_PI / (3 * SCREEN_WIDTH)) {
        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = sin(ray_angle);

        double x = player->x;
        double y = player->y;

        map_x = (int)x;
        map_y = (int)y;

        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - y) * delta_dist_y;
        }

        while (!hit) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_y][map_x] > 0) hit = 1;
        }

        if (side == 0) perp_wall_dist = (map_x - x + (1 - step_x) / 2) / ray_dir_x;
        else perp_wall_dist = (map_y - y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

        if (side == 0) mlx_pixel_put(mlx_ptr, win_ptr, map_x * TILE_SIZE, (draw_start + draw_end) / 2 * TILE_SIZE, 0xFF0000);
        else mlx_pixel_put(mlx_ptr, win_ptr, (draw_start + draw_end) / 2 * TILE_SIZE, map_y * TILE_SIZE, 0xFF0000);
    }
}

void draw_screen(void *mlx_ptr, void *win_ptr, t_player *player) {
    double screen_x, screen_y;
    screen_x = player->x + SCREEN_WIDTH * cos(player->angle);
    screen_y = player->y + SCREEN_WIDTH * sin(player->angle);
    mlx_pixel_put(mlx_ptr, win_ptr, screen_x, screen_y, SCREEN_COLOR);
}

int key_press(int keycode, void *param) {
    t_player *player = (t_player*)param;
    if (keycode == 53) // Esc key
        exit(0);
    else if (keycode == 124) // Right arrow key
        player->angle += M_PI / 30;
    else if (keycode == 123) // Left arrow key
        player->angle -= M_PI / 30;
    return (0);
}

int draw(void *param) {
    t_minimap *minimap = (t_minimap*)param;
    void *mlx_ptr = minimap->mlx_ptr;
    void *win_ptr = minimap->win_ptr;
    t_player *player = minimap->player;

    // Effacer la fenêtre
    mlx_clear_window(mlx_ptr, win_ptr);

    // Dessiner la carte
    // (À compléter selon votre configuration de carte)

    // Dessiner le joueur
    draw_player(mlx_ptr, win_ptr, player);

    // Dessiner les rayons
    draw_rays(mlx_ptr, win_ptr, player, minimap->map);

    // Dessiner l'écran
    draw_screen(mlx_ptr, win_ptr, player);

    return (0);
}

int main() {
    t_minimap minimap;
    t_player player;

    player.x = 50;
    player.y = 50;
    player.angle = M_PI / 4; // 45 degrees
    minimap.player = &player;
    minimap.mlx_ptr = mlx_init();
    minimap.win_ptr = mlx_new_window(minimap.mlx_ptr, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "MiniMap");

    // Déclaration de la carte
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    minimap.map = map;

    mlx_hook(minimap.win_ptr, 2, 0, key_press, &minimap);
    mlx_loop_hook(minimap.mlx_ptr, draw, &minimap);
    mlx_loop(minimap.mlx_ptr);

    return 0;
}