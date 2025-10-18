/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:17:34 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 14:30:00 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_fov_120(t_data *data, int cx, int cy, t_pixel *pixel)
{
	int		radius;
	int		x;
	int		y;
	double	rad;
	double	player_angle;

	player_angle = atan2(data->dir_y, data->dir_x);
	pixel->color = 0xF0D3D3;
	radius = 0;
	while (++radius <= 20)
	{
		pixel->angle = -61;
		while (++pixel->angle <= 60)
		{
			rad = player_angle + (pixel->angle * M_PI / 180.0);
			x = cx + (int)(radius * cos(rad));
			y = cy + (int)(radius * sin(rad));
			pixel->x = x;
			pixel->y = y;
			if (pixel->x >= 0 && pixel->x < WIDTH && pixel->y >= 0
				&& pixel->y < HEIGHT)
				put_pixel_with_struct(pixel);
		}
	}
}

void	draw_player_marker(t_data *data, int dst_off_x, int dst_off_y)
{
	int		cx;
	int		cy;
	int		dx;
	int		dy;
	t_pixel	pixel;

	cx = dst_off_x + data->minimap.view_w / 2;
	cy = dst_off_y + data->minimap.view_h / 2;
	init_raw_data(&pixel, data);
	draw_fov_120(data, cx, cy, &pixel);
	pixel.color = 0x00FF0000;
	dy = -2;
	while (++dy <= 2)
	{
		dx = -2;
		while (++dx <= 2)
		{
			pixel.x = cx + dx;
			pixel.y = cy + dy;
			if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0
				&& pixel.y < HEIGHT)
				put_pixel_with_struct(&pixel);
		}
	}
}
