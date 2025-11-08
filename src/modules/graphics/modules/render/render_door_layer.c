/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_layer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:57:36 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perform_background_dda(t_data *data, t_ray *bg_ray)
{
	while (bg_ray->hit == 0)
	{
		if (bg_ray->side_dist_x < bg_ray->side_dist_y)
		{
			bg_ray->side_dist_x += bg_ray->delta_dist_x;
			bg_ray->map_x += bg_ray->step_x;
			bg_ray->side = 0;
		}
		else
		{
			bg_ray->side_dist_y += bg_ray->delta_dist_y;
			bg_ray->map_y += bg_ray->step_y;
			bg_ray->side = 1;
		}
		if (data->map[bg_ray->map_y][bg_ray->map_x] == '1')
			bg_ray->hit = 1;
	}
}

static void	calculate_background_wall(t_data *data, t_ray *bg_ray)
{
	if (bg_ray->side == 0)
		bg_ray->perp_wall_dist = (bg_ray->map_x - data->player_x + (1
					- bg_ray->step_x) / 2.0) / bg_ray->ray_dir_x;
	else
		bg_ray->perp_wall_dist = (bg_ray->map_y - data->player_y + (1
					- bg_ray->step_y) / 2.0) / bg_ray->ray_dir_y;
	determine_texture(bg_ray);
	bg_ray->line_height = (int)(HEIGHT / bg_ray->perp_wall_dist);
	bg_ray->draw_start = -bg_ray->line_height / 2 + HEIGHT / 2;
	if (bg_ray->draw_start < 0)
		bg_ray->draw_start = 0;
	bg_ray->draw_end = bg_ray->line_height / 2 + HEIGHT / 2;
	if (bg_ray->draw_end >= HEIGHT)
		bg_ray->draw_end = HEIGHT - 1;
}

static void	render_background_wall(t_data *data, t_ray *ray, int x)
{
	t_ray	bg_ray;

	bg_ray = *ray;
	bg_ray.hit = 0;
	perform_background_dda(data, &bg_ray);
	calculate_background_wall(data, &bg_ray);
	render_floor_ceiling(data, x, bg_ray.draw_end);
	render_textured_wall(data, &bg_ray, x);
}

void	render_door_column_layered(t_data *data, t_ray *ray, int x)
{
	t_door	*door;
	int		tex_x;
	double	step;

	door = get_door_at_position(data, ray->map_x, ray->map_y);
	calculate_texture_coords(data, ray, &tex_x, &step);
	if (door && door->open_offset > 0.01 && !ray_hits_door_texture(data, tex_x,
			door))
		render_background_wall(data, ray, x);
	if (door && door->open_offset < 0.99 && ray_hits_door_texture(data, tex_x,
			door))
		draw_door_column(data, ray, x, tex_x);
}
