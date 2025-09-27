#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include "libft.h"

void	perform_dda(t_ray *ray, t_data *data)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        
        if (ray->map_x < 0 || ray->map_y < 0 || 
            ray->map_y >= data->map_height || 
            ray->map_x >= (int)ft_strlen(data->map[ray->map_y]) ||
            data->map[ray->map_y][ray->map_x] == '1')
        {
            ray->hit = 1;
        }
    }
}

void	calculate_wall_distance(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player_x + (1 - ray->step_x)
				/ 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player_y + (1 - ray->step_y)
				/ 2.0) / ray->ray_dir_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}
