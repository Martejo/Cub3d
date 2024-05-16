#include "../../minilibx-linux/mlx.h"
#include "../../minilibx-linux/mlx_int.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

# define FOV 66
# define FOV_RAD (FOV * M_PI/180)
# define PLANE_FOV tan(FOV_RAD / 2)
# define SCREEN_WIDTH 800

# define PLAYER_STEP_SIZE 5

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

// typedef struct s_ray
// {
//     int r;
//     int mx;
//     int my;
//     int mp;
//     int dof;
//     float rx;
//     float ry;
//     float ra;
//     float xo;
//     float yo;
// } t_ray;



typedef struct s_player //retirer les mots relative et ajouter gr_ devant les variables positionnees sur la grille
{
    //ce qui peut etre modif par un button
    t_dvector   pos;  //(grid)
    double      relative_dir_angle;  //(player.pos) c'es cette valeur que l'on fait varier a l'appui d'un bouton

    //ce qui nous sert a calculer le raycasting
    t_dvector   dir;  //(grid) utile ?
    t_dvector   plane;  //(grid) utile ?

    t_dvector   relative_dir;  //(player.pos)
    t_dvector   relative_plane; //(player_dir)
    t_dvector   rel_next_step;  //(grid) deltaX => distance du pas du joueur sert a calculer next pos
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

typedef struct s_ray
{
    // t_ivector nearest_grid_pos;
    t_ivector pos; //apeler pos//(tombe toujours sur la grille puisqu 'arrondi) //utiliser des int permet de se placer exactement sur un elem de la grille (espace ou mur)
    t_dvector true_pos; // = player pos
    t_dvector dir; // (grid) ou (player pos)?
    
    //calcul DDA 
    t_dvector delta_dist; // distance entre player pos et la 1re coordonnee de grille rencontree (ray_pos)
    t_dvector side_dist; // distance entre player pos et la 1re coordonnee de grille rencontree (ray_pos)
    // t_dvector delta_dist; //valeur absolue de dir, sert a 
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



bool is_wall_detected(const t_grid *grid, const t_ray *ray)
{
    return (grid->content[ray->pos.y][ray->pos.x] == 1); //le ray se trouve sur un mur
}

double  process_wall_dist(char last_size_tested, const t_ray *ray)
{
     
    if (last_size_tested == 'x')
        return((ray->pos.x - player->pos.x + (1 - stepX) / 2) / rayDirX);
    else
        return((mapY - posY + (1 - stepY) / 2) / rayDirY);
}

void find_wall_distance_dda(const t_grid *grid, t_ray *ray)
{
    bool hit; // bool
    char last_side_tested;
    while (!hit)
        {
            //move ray pos
            if (ray->side_dist.x < ray->side_dist.y) //si ray
            {
                ray->side_dist.x += ray->delta_dist.x;
                ray->pos.x += ray->step_direction.x;
                last_side_tested = 'x';
            }
            else
            {
                ray->side_dist.y += ray->delta_dist.y;
                ray->pos.y += ray->step_direction.y;
                last_side_tested = 'y';
            }
            hit = is_wall_detected(grid, ray);
        }
    return(process_wall_dist(last_side_tested, ray))
}

void init_ray(const double camera_x, t_player *player, t_ray *ray)
{
    ray->true_pos.x = player->pos.x;//je crois qu' un int est utilise simplement pour tracer le pixel sur la minimap
    ray->true_pos.y = player->pos.y;//je crois qu' un int est utilise simplement pour tracer le pixel sur la minimap
    ray->pos.x = (int) player->pos.x;//je crois qu' un int est utilise simplement pour tracer le pixel sur la minimap
    ray->pos.y = (int) player->pos.y;
    //on ne lance pas les rayons a partir du player mais a partir de la camera(pour pallier a l' effet fisheye)
    ray->dir.x = player->plane.x * camera_x;
    ray->dir.y = player->plane.y * camera_x;
}


void prepare_dda_ray(const t_player *player, t_ray *ray)
{
    // delta dist x distance entre les differentes colonnes de la grille (depend de la direction du rayon) 
    // side dist x distance entre player pos et la 1re coordonnee de colonne de grille rencontree (ray_pos)
    // step = sens qui est suivi par le rayon (gauche droite pour step.x) (haut bas pour step.y)
    
    ray->delta_dist.x = fabs(ray->dir.x);
    ray->delta_dist.y = fabs(ray->dir.y);
    if (ray->dir.x < 0)
    {
        ray->step_direction.x = -1;
        ray->side_dist.x = (ray->true_pos.x - ray->pos.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step_direction.x = 1;
        ray->side_dist.x = (ray->pos.x + 1.0 - ray->true_pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step_direction.y = -1;
        ray->side_dist.y = (ray->true_pos.y - ray->pos.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step_direction.y = 1;
        ray->side_dist.y = (ray->pos.y + 1.0 - ray->true_pos.y) * ray->delta_dist.y;
    }
    //le vecteur entre le 1er rayon et le mur sera donc 
}



void display_raycast_img(t_cub3d *data)
{
	t_ray ray;
    t_player *player = &(data->player);
    double  wall_dist; //distance du mur perpendiculaire le plus proche
    double  camera_x; //distance du mur perpendiculaire le plus proche

	for (int x = 0; x < 800; x++)
    {
        camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        init_ray(camera_x, player, &ray);
        prepare_dda_ray();
        
        wall_dist = find_wall_distance_dda();
       

        // Calculate height of line to draw on screen
        int lineHeight = (int)(600 / perpWallDist);

        // draw the pixels of the stripe as a vertical line
        for(int y = (600 - lineHeight) / 2; y < (600 + lineHeight) / 2; y++)
            mlx_pixel_put(data.mlx, data.mlx_win, x, y, 0xFFFFFF); // Assume 0xFFFFFF is the color of the wall
		 
    }
}

// void display_raycast_img(t_cub3d data)
// {
// 	t_raycast raycast;
//     double posX = data.playerX / data.grid.size; // Position du joueur en coordonnées carte
//     double posY = data.playerY / data.grid.size;
//     printf("pX %f PY %f\n", posX, posY);
// 	double dirX = cos(data.playerAngle);
//     double dirY = sin(data.playerAngle);
// 	printf(" dirX %f, dirY %f\n", dirX, dirY);
//     double planeX = 0.66 * -dirY; // Plan de la caméra pour créer le FOV
//     double planeY = 0.66 * dirX;
// 	printf(" planeX %f, planeY %f\n", planeX, planeY);

//     // Afficher la direction du joueur
//     // double dirX_map = posX + dirX; // 5 est une constante pour la longueur de la ligne directionnelle
//     // double dirY_map = posY + dirY;
    
// 	printf("ecran start X %f ecran start Y %f\n", posX + dirX + planeX, posY + dirY + planeY);
//     printf("ecran end X %f ecran end Y %f\n", posX + dirX - planeX, posY + dirY - planeY);
// 	for (int x = 0; x < 800; x++)
//     {
//         double cameraX = 2 * x / (double)800 - 1;
//         double rayDirX = dirX + planeX * cameraX;
//         double rayDirY = dirY + planeY * cameraX;

//         int mapX = (int)posX;
//         int mapY = (int)posY;

//         double sideDistX;
//         double sideDistY;

//         double deltaDistX = fabs(data.grid.size/ rayDirX);
//         double deltaDistY = fabs(data.grid.size/ rayDirY);
//         double perpWallDist;

//         int stepX;
//         int stepY;

//         int hit = 0;
//         int side;

//         if (rayDirX < 0)
//         {
//             stepX = -1;
//             sideDistX = (posX - mapX) * deltaDistX;
//         }
//         else
//         {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//         }
//         if (rayDirY < 0)
//         {
//             stepY = -1;
//             sideDistY = (posY - mapY) * deltaDistY;
//         }
//         else
//         {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//         }

//         while (hit == 0)
//         {
//             if (sideDistX < sideDistY)
//             {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//             }
//             else
//             {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//             }
//             if (data.map[mapY][mapX] > 0)
// 			{
//                 hit = 1;
// 				//printf("HIT\n");
// 			}
//         }

//         if (side == 0)
//             perpWallDist = (sideDistX - deltaDistX);
//         else
//             perpWallDist = (sideDistY - deltaDistY);

//         if (side == 0)
//             perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//         else 
//             perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

//         // Calculate height of line to draw on screen
//         int lineHeight = (int)(600 / perpWallDist);

//         // draw the pixels of the stripe as a vertical line
//         for(int y = (600 - lineHeight) / 2; y < (600 + lineHeight) / 2; y++)
//             mlx_pixel_put(data.mlx, data.mlx_win, x, y, 0xFFFFFF); // Assume 0xFFFFFF is the color of the wall
		 
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

void modif_player_pos(int key, t_player *player)
{
    //mouvements haut bas
    if (key == XK_w)
    {
        player->pos.x += player->rel_next_step.x;
        player->pos.y += player->rel_next_step.y;
    }
    if (key == XK_s)
    {
        player->pos.x -= player->rel_next_step.x;
        player->pos.y -= player->rel_next_step.y;
    }

    //mouvements lateraux pas sur de ces calculs reverifier (inversion )
    if (key == XK_a)
    {
        player->pos.x += player->rel_next_step.y;
        player->pos.y += player->rel_next_step.x;
    }
    if (key == XK_d)
    {
        player->pos.x -= player->rel_next_step.y;
        player->pos.y -= player->rel_next_step.x;
    }
}

void modif_player_rel_next_step(t_player *player)
{
    player->rel_next_step.x = cos(player->relative_dir_angle) * PLAYER_STEP_SIZE;
    player->rel_next_step.y = sin(player->relative_dir_angle) * PLAYER_STEP_SIZE;
}

void modif_player_dir(int key, t_player *player)
{
    if (key == XK_Right)
    {
        player->relative_dir_angle -= 0.1;
        if (player->relative_dir_angle < 0)
            player->relative_dir_angle += 2 * PI;
    }
    if (key == XK_Left)
    {
        player->relative_dir_angle += 0.1;
        if (player->relative_dir_angle > 2 * PI)
            player->relative_dir_angle -= 2 * PI;
    }
}

int modif_player(int key, t_cub3d *data)
{
    mlx_clear_window(data->mlx, data->mlx_win);
    if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
        modif_player_pos(key, &(data->player));
    if (key == XK_Left || key == XK_Right);
    {
        modif_player_dir(key, &(data->player));
        modif_player_rel_next_step(&(data->player));
    }
    display_raycast_img(data);
    // draw_map(*data);
    // draw_player(*data);
    return (0);
}

void init_player(t_cub3d const *data, t_player *player)
{
    player->pos.x = 1; //cela dependra de pos du joueur sur la grid (on le place sur grid_x = 1 pour le mom)
    player->pos.y = 1; //cela dependra de pos du joueur sur la grid (on le place sur grid_y = 1 pour le mom)
    player->relative_dir_angle = to_rad(45); //cela dependra de la dir du joueur sur la grid (on part sur un angle a 45deg) 
    player->relative_dir.x = cos(player->relative_dir_angle); //cela dependra de la dir du joueur sur la grid (on part sur un angle a 45deg) 
    player->relative_dir.y = sin(player->relative_dir_angle); //cela dependra de la dir du joueur sur la grid (on part sur un angle a 45deg) 
    player->relative_plane.x = player->dir.x + tan(FOV_RAD/2); //par rapport a playerdir
    player->relative_plane.y = 0; //inutile
    player->rel_next_step.x = player->relative_dir.x * PLAYER_STEP_SIZE;
    player->rel_next_step.y = player->relative_dir.y * PLAYER_STEP_SIZE;

    // ces valeurs sont par rapport a la grille mais sont elles utiles ?
    player->dir.x = player->pos.x + player->relative_dir.x;
    player->dir.y = player->pos.y + player->relative_dir.y;
    player->plane.x = player->dir.x + player->relative_plane.x;
    player->plane.y = player->dir.y + player->relative_plane.y; //pas sur de ce calcul
}

//void move_player(t_cub3d const *data, t_player *player); //hook
// {
//     //bouger la pos si certaines touches sont appuyees
//     //bouger la dir si certaines touches sont appuyees (pas de modif si c'est la pos qui bouge)
//     //remettre a jour les valeurs de plane
// }

void init_grid(t_cub3d const *data, t_grid *grid)
{
    grid->content = g_grid; //mettre la grille parsee dnas cette var au moment du parsing
    int i;
    int len_line;
    
    len_line = 0;
    i = 0;
    grid->width = 0;
    while (grid->content[i])
    {
        len_line = ft_strlen(g_grid[0]);
        if (len_line > grid->width)
            grid->width = len_line; //attention si la map n' est pas carree
        i++;
    }
    grid->height = i;
    grid->size = grid->width * grid->height;
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

    //init player 
    init_player(&data, &(data.player));
    init_grid(&data, &(data.player));
    memset(&data.ray, 0, sizeof(t_ray));

    // Boucle pour garder la fenêtre ouverte
    // draw_map(data);
    // draw_player(data);
	display_raycast_img(data);
    mlx_hook(data.mlx_win, 2, 1L << 0, modif_player, &data);
    mlx_loop(data.mlx);
    return (0);
}
