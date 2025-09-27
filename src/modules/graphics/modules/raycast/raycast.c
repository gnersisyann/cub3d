#include "cub3d.h"
#include "graphics.h"
#include "defines.h"

void	cast_single_ray(t_data *data, int x, double ray_dir_x, double ray_dir_y)
{
    t_ray	ray;
    
    init_ray(&ray, data, ray_dir_x, ray_dir_y);
    calculate_step_and_side_dist(&ray, data);
    perform_dda(&ray, data);
    calculate_wall_distance(&ray, data);
    draw_wall_stripe(data, &ray, x);
}

void	cast_rays(t_data *data)
{
    int		x;
    double	camera_x;
    double	ray_dir_x;
    double	ray_dir_y;

    x = 0;
    while (x < WIDTH)
    {
        camera_x = 2 * x / (double)WIDTH - 1;
        ray_dir_x = data->dir_x + data->plane_x * camera_x;
        ray_dir_y = data->dir_y + data->plane_y * camera_x;
        
        cast_single_ray(data, x, ray_dir_x, ray_dir_y);
        x++;
    }
}

