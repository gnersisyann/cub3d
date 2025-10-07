/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:41:36 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/04 16:59:42 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include <math.h>

void	render_floor_ceiling(t_data *data, int x, int draw_end)
{
	int	y;

	y = -1;
	while (++y < HEIGHT / 2)
		my_mlx_pixel_put(data, x, y, data->ceiling_color);
	y = draw_end - 1;
	while (++y < HEIGHT)
		my_mlx_pixel_put(data, x, y, data->floor_color);
}

void	calculate_texture_coords(t_data *data, t_ray *ray, int *tex_x,
		double *step)
{
	t_texture	*texture;
	double		wall_x;

	texture = get_current_texture_frame(data, ray->texture_num);
	if (!texture)
		return ;
	if (ray->side == 0)
		wall_x = data->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		*tex_x = texture->width - *tex_x - 1;
	*step = 1.0 * texture->height / ray->line_height;
}

void	draw_texture_column(t_data *data, t_ray *ray, int x, int tex_x)
{
	double		step;
	double		tex_pos;
	int			y;
	int			color;
	t_texture	*texture;

	texture = get_current_texture_frame(data, ray->texture_num);
	if (!texture)
		return ;
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_height / 2.0) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = get_texture_pixel(texture, tex_x,
				(int)tex_pos & (texture->height - 1));
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(data, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	render_textured_wall(t_data *data, t_ray *ray, int x)
{
	int		tex_x;
	double	step;

	calculate_texture_coords(data, ray, &tex_x, &step);
	draw_texture_column(data, ray, x, tex_x);
}

void	render_wall_column(t_data *data, t_ray *ray, int x)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	render_floor_ceiling(data, x, ray->draw_end);
	render_textured_wall(data, ray, x);
}
