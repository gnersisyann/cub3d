/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:41:38 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 17:53:00 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_single_ray(t_data *data, int x, double ray_dir_x, double ray_dir_y)
{
	t_ray	ray;

	init_ray(&ray, data, ray_dir_x, ray_dir_y);
	calculate_step_and_side_dist(&ray, data);
	perform_dda(data, &ray);
	data->z_buffer[x] = ray.perp_wall_dist;
	render_wall_column(data, &ray, x);
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
