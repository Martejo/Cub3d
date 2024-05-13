#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

typedef struct s_cub3d
{
	void			*mlx;
	void			*mlx_win;
	int (*map)[8];
	int	mapSize;
	float		playerX;
	float		playerY;
	float	playerAngle;
	float	deltaX;
	float	deltaY;
	
}	t_cub3d;

#define W 122
#define A 113
#define S 115
#define D 100
#define PI  3.1415926535


void draw_ray(t_cub3d data)
{
    int rayLength = 50;  // Longueur du rayon à dessiner
    // Calculer le centre du cube joueur
    double centerX = data.playerX + 4;  // +4 pour se centrer sur le cube de 8x8 pixels
    double centerY = data.playerY + 4;  // +4 pour se centrer sur le cube de 8x8 pixels

    double endX = centerX + cos(data.playerAngle) * rayLength;
    double endY = centerY + sin(data.playerAngle) * rayLength;

    // Dessiner une ligne du joueur à la fin du rayon
    double deltaX = endX - centerX;
    double deltaY = endY - centerY;
    int steps = fmax(fabs(deltaX), fabs(deltaY));  // Nombre de pas pour la boucle, basé sur la plus grande différence

    for (int i = 0; i <= steps; i++) {
        int x = centerX + deltaX * i / steps;
        int y = centerY + deltaY * i / steps;
        mlx_pixel_put(data.mlx, data.mlx_win, x, y, 0xFF0000);  // Utilisez une couleur rouge pour le rayon
    }
}


void	draw_player(t_cub3d data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			 mlx_pixel_put(data.mlx, data.mlx_win, data.playerX+x, data.playerY+y, 0xFFFFFF);
			 x++;
		}
		y++;	
	}
}


void	draw_map(t_cub3d data)
{
    int	x;
    int	y;
    int	i;  // Variable pour la boucle interne horizontale
    int	j;  // Variable pour la boucle interne verticale

    y = 0;
    while (y < 8)
    {
        x = 0;
        while (x < 8)
        {
            if (data.map[y][x] == 1)
            {
                j = 0;
                while (j < 64)  // Boucle pour la hauteur du carré
                {
                    i = 0;
                    while (i < 64)  // Boucle pour la largeur du carré
                    {
                        mlx_pixel_put(data.mlx, data.mlx_win, x * 64 + i, y * 64 + j, 0xFFFFFF);
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
    for (int gridY = 0; gridY <= 8; gridY++)  // Lignes horizontales
    {
        for (int pixel = 0; pixel < 8 * 64; pixel++)  // 8 cellules * 64 pixels par cellule
        {
            mlx_pixel_put(data.mlx, data.mlx_win, pixel, gridY * 64, 0x0000FF); // Ligne bleue
        }
    }
    for (int gridX = 0; gridX <= 8; gridX++)  // Lignes verticales
    {
        for (int pixel = 0; pixel < 8 * 64; pixel++)
        {
            mlx_pixel_put(data.mlx, data.mlx_win, gridX * 64, pixel, 0x0000FF); // Ligne bleue
        }
    }
}


int	buttons(int key, t_cub3d *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	if (key == W)
	{
		data->playerX += data->deltaX;
		data->playerY += data->deltaY;
	}
	if (key == A)
	{
		data->playerAngle -= 0.1;
		if (data->playerAngle < 0)
			data->playerAngle += 2 * PI;
		data->deltaX = cos(data->playerAngle) * 5;
		data->deltaY = sin(data->playerAngle) * 5;
	}
	if (key == S)
	{
		data->playerX -= data->deltaX;
		data->playerY -= data->deltaY;
	}
	if (key == D)
	{
		data->playerAngle += 0.1;
		if (data->playerAngle > 2 * PI)
			data->playerAngle -= 2 * PI;
		data->deltaX = cos(data->playerAngle) * 5;
		data->deltaY = sin(data->playerAngle) * 5;
	}
	draw_map(*data);
	draw_player(*data);
	draw_ray(*data); 
	return (0);
}

int main()
{
	t_cub3d data;
 	data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 800, 600, "Raycaster");
	data.playerX = 300;
	data.playerY = 300;
	data.deltaX = cos(data.playerAngle) * 5;
	data.deltaY = sin(data.playerAngle) * 5;
	data.mapSize = 64;
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
	draw_ray(data); 
	mlx_hook(data.mlx_win, 2, 1L<<0, buttons, &data);
    mlx_loop(data.mlx);
    return (0);
}
