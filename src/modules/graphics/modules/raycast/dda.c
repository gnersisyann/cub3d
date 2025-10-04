/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:41:42 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/04 16:51:44 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"

void	determine_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->texture_num = 3;
		else
			ray->texture_num = 2;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->texture_num = 1;
		else
			ray->texture_num = 0;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	ray->hit = 0;
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
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player_x + (1 - ray->step_x)
				/ 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player_y + (1 - ray->step_y)
				/ 2.0) / ray->ray_dir_y;
	determine_texture(ray);
}
