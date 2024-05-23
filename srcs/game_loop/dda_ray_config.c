#include "../../includes/cub3d.h"

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