


#include "./minilibx-linux/mlx.h"
#include <math.h>

void ray_casting(void *mlx_ptr, void *win_ptr, int map[4][6]) {
    
    int w = 800, h = 600;
    double posX = 1.5; // Position initiale X du joueur
    double posY = 1.5; // Position initiale Y du joueur
    double dirX = 0.0; // Direction initiale X du joueur (sud)
    double dirY = 1.0; // Direction initiale Y du joueur (sud)
    double FOV = 140.0; // FOV de 60 degrés
    double FOV_rad = FOV * M_PI / 180.0; // Conversion en radians

    double planeX = dirY * tan(FOV_rad / 2.0);
    double planeY = -dirX * tan(FOV_rad / 2.0);
    for (int x = 0; x < w; x++) {
        double cameraX = 2 * x / (double)w - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX, stepY;
        int hit = 0; // was there a wall hit?
        int side; // was a NS or a EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0) {
            // jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (map[mapY][mapX] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction
        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(h / perpWallDist);

        // draw the pixels of the stripe as a vertical line
        for(int y = (h - lineHeight) / 2; y < (h + lineHeight) / 2; y++)
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF); // Assume 0xFFFFFF is the color of the wall
    }
}


int main()
{
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Raycaster");

	int map[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1}
};


    // Boucle pour garder la fenêtre ouverte
	ray_casting(mlx_ptr, win_ptr, map);
    mlx_loop(mlx_ptr);
    return (0);
}
