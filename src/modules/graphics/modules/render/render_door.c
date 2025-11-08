/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:57:33 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_door_render(t_door_render *dr, t_data *data, t_ray *ray)
{
	dr->texture = get_current_texture_frame(data, 4);
	dr->door = get_door_at_position(data, ray->map_x, ray->map_y);
	dr->step = 1.0 * dr->texture->height / ray->line_height;
	dr->tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_height / 2.0)
		* dr->step;
}

static int	get_adjusted_tex_x(t_texture *texture, t_door *door, int tex_x)
{
	return (tex_x - (int)(door->open_offset * texture->width));
}

void	draw_door_column(t_data *data, t_ray *ray, int x, int tex_x)
{
	t_door_render	dr;
	int				adjusted_tex_x;
	int				color;
	int				y;

	init_door_render(&dr, data, ray);
	if (!dr.texture || !dr.door)
		return ;
	adjusted_tex_x = get_adjusted_tex_x(dr.texture, dr.door, tex_x);
	if (adjusted_tex_x < 0 || adjusted_tex_x >= dr.texture->width)
		return ;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = get_texture_pixel(dr.texture, adjusted_tex_x,
				(int)dr.tex_pos & (dr.texture->height - 1));
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(data, x, y, color);
		dr.tex_pos += dr.step;
		y++;
	}
}

int	ray_hits_door_texture(t_data *data, int tex_x, t_door *door)
{
	t_texture	*texture;
	int			adjusted_tex_x;

	texture = get_current_texture_frame(data, 4);
	if (!texture)
		return (0);
	adjusted_tex_x = get_adjusted_tex_x(texture, door, tex_x);
	if (adjusted_tex_x >= 0 && adjusted_tex_x < texture->width)
		return (1);
	return (0);
}
