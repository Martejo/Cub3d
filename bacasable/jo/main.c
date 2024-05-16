#include "../../minilibx-linux/mlx.h"
#include "../../minilibx-linux/mlx_int.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

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

typedef struct s_cub3d
{
    void *mlx;
    void *mlx_win;
    t_ray ray;
    int (*map)[8];
    int mapX;
    int mapY;
    int mapSize;
    float playerX;
    float playerY;
    float playerAngle;
    float deltaX;
    float deltaY;
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
	
    double posX = data.playerX / data.mapSize; // Position du joueur en coordonnées carte
    double posY = data.playerY / data.mapSize;
    printf("pX %f PY %f\n", posX, posY);
	double dirX = cos(data.playerAngle);
    double dirY = sin(data.playerAngle);
	printf(" dirX %f, dirY %f\n", dirX, dirY);
    double planeX = 0.66 * -dirY; // Plan de la caméra pour créer le FOV
    double planeY = 0.66 * dirX;
	printf(" planeX %f, planeY %f\n", planeX, planeY);

    // Afficher la direction du joueur
    double dirX_map = posX + dirX; // 5 est une constante pour la longueur de la ligne directionnelle
    double dirY_map = posY + dirY;
    
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

        double deltaDistX = fabs(data.mapSize / rayDirX);
        double deltaDistY = fabs(data.mapSize / rayDirY);
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
		//printf("perpwalldist = %f\n", perpWallDist);
        double rayLength = perpWallDist / data.mapSize;

        double currentX = posX + rayDirX * rayLength;
        double currentY = posY + rayDirY * rayLength;

        int drawX_start = (int)(posX * data.mapSize);
        int drawY_start = (int)(posY * data.mapSize);
        int drawX_end = (int)(currentX * data.mapSize);
        int drawY_end = (int)(currentY * data.mapSize);

		//affiche le screen
		draw_line(data.mlx, data.mlx_win, (posX + dirX + planeX) * data.mapSize, (posY + dirY + planeY) * data.mapSize, (posX + dirX - planeX) * data.mapSize, (posY + dirY - planeY) * data.mapSize,  0xFFFFFF);
   		//affiche direction
		draw_line(data.mlx, data.mlx_win, posX * data.mapSize, posY * data.mapSize, dirX_map * data.mapSize, dirY_map * data.mapSize, 0x00FF00); // Ligne verte pour la direction
		//affiche les rayons
        draw_line(data.mlx, data.mlx_win, drawX_start, drawY_start, drawX_end, drawY_end, 0xFF0000); // Dessinez le rayon en rouge
		  // Calculate distance projected on camera direction
    //       if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    //   else          perpWallDist = (sideDistY - deltaDistY);
        
        //partie pour le raytracing
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


// void draw_ray_dir(t_cub3d data)
// {
//     int rayLength = 50; // Longueur du rayon à dessiner
//     // Calculer le centre du cube joueur
//     double centerX = data.playerX + 4; // +4 pour se centrer sur le cube de 8x8 pixels
//     double centerY = data.playerY + 4; // +4 pour se centrer sur le cube de 8x8 pixels

//     double dirX_map = centerX + cos(data.playerAngle) * rayLength;
//     double dirY_map = centerY + sin(data.playerAngle) * rayLength;

//     // Dessiner une ligne du joueur à la fin du rayon
//     double deltaX = dirX_map - centerX;
//     double deltaY = dirY_map - centerY;
//     int steps = fmax(fabs(deltaX), fabs(deltaY)); // Nombre de pas pour la boucle, basé sur la plus grande différence

//     for (int i = 0; i <= steps; i++)
//     {
//         int x = centerX + deltaX * i / steps;
//         int y = centerY + deltaY * i / steps;
//         mlx_pixel_put(data.mlx, data.mlx_win, x, y, 0xFF0000); // Utilisez une couleur rouge pour le rayon
//     }
// }

// void draw_player(t_cub3d data)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < 10)
//     {
//         x = 0;
//         while (x < 10)
//         {
//             mlx_pixel_put(data.mlx, data.mlx_win, data.playerX + x, data.playerY + y, 0xFFFFFF);
//             mlx_pixel_put(data.mlx, data.mlx_win, data.playerX - x, data.playerY - y, 0x0000FF);
//             x++;
//         }
//         y++;
//     }
// }

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
                while (j < data.mapSize) // Boucle pour la hauteur du carré
                {
                    i = 0;
                    while (i < data.mapSize) // Boucle pour la largeur du carré
                    {
                        mlx_pixel_put(data.mlx, data.mlx_win, x * data.mapSize + i, y * data.mapSize + j, 0x0000FF);
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
        for (int pixel = 0; pixel < 8 * data.mapSize; pixel++) // 8 cellules * data.mapSize pixels par cellule
        {
            mlx_pixel_put(data.mlx, data.mlx_win, pixel, gridY * data.mapSize, 0x0000FF); // Ligne bleue
        }
    }
    for (int gridX = 0; gridX <= 8; gridX++) // Lignes verticales
    {
        for (int pixel = 0; pixel < 8 * data.mapSize; pixel++)
        {
            mlx_pixel_put(data.mlx, data.mlx_win, gridX * data.mapSize, pixel, 0x0000FF); // Ligne bleue
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
    draw_map(*data);
    draw_player(*data);
    return (0);
}

int main()
{
    t_cub3d data;
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 800, 600, "Raycaster");
    data.mapSize = 64;
    data.playerX = data.mapSize;
    data.playerY = data.mapSize;
    data.playerAngle = 45; // Initialisation de playerAngle
    data.deltaX = cos(data.playerAngle) * 5;
    data.deltaY = sin(data.playerAngle) * 5;
    data.mapX = 8;
    data.mapY = 8;
    memset(&data.ray, 0, sizeof(t_ray));
    int mape[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
    };
    data.map = mape;

    // Boucle pour garder la fenêtre ouverte
    draw_map(data);
    draw_player(data);
	draw_ray_dir(data);
    mlx_hook(data.mlx_win, 2, 1L << 0, buttons, &data);
    mlx_loop(data.mlx);
    return (0);
}
