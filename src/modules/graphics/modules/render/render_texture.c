/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:57:31 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture_column(t_data *data, t_ray *ray, int x, int tex_x)
{
	t_texture	*texture;
	double		step;
	double		tex_pos;
	int			y;
	int			color;

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
