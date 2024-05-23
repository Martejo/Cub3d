#include "../../includes/cub3d.h"

static bool is_wall_detected(const t_grid *grid, const t_ray *ray)
{
    return (grid->content[ray->grid_pos.y][ray->grid_pos.x] == 1);
}

static double process_wall_dist(char last_side_tested, const t_ray *ray)
{
    if (last_side_tested == 'x')
        return ((ray->grid_pos.x - ray->true_pos.x + (1 - ray->step_direction.x) / 2) / ray->dir.x);
    else
        return ((ray->grid_pos.y - ray->true_pos.y + (1 - ray->step_direction.y) / 2) / ray->dir.y);
}

static char process_wall_orientation(const t_ray *ray, char last_side_tested)
{
    if (last_side_tested == 'x')
    {
        if (ray->dir.x > 0)
            return 'E'; // East blue
        else
            return 'W'; // West yellow
    }
    else
    {
        if (ray->dir.y > 0)
            return 'S'; // South green
        else
            return 'N'; // North red
    }
}

void get_wall_config_dda(const t_player *player, const t_grid *grid, t_ray *ray, t_dda *wall_config)
{
    bool hit = false;
    char last_side_tested;

    (void) player;//
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
    wall_config->orientation = process_wall_orientation(ray, last_side_tested);
}