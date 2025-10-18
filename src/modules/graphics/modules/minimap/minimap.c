/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:30:18 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 14:30:19 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_miniview_pixels(t_data *data, t_norm *norm)
{
	t_coords	coords;

	init_raw_data(&coords.pixel, data);
	coords.y = -1;
	while (++coords.y < data->minimap.view_h)
	{
		coords.screen_y = norm->dst_off_y + coords.y;
		if (coords.screen_y < 0 || coords.screen_y >= HEIGHT)
			continue ;
		coords.x = -1;
		while (++coords.x < data->minimap.view_w)
		{
			coords.screen_x = norm->dst_off_x + coords.x;
			if (coords.screen_x < 0 || coords.screen_x >= WIDTH)
				continue ;
			coords.src_x = norm->start_px + coords.x;
			coords.src_y = norm->start_py + coords.y;
			if (check_miniview_bounds(data, &coords))
				process_miniview_pixel(data, &coords);
		}
	}
}

static void	draw_minimap_helper(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			color = get_minimap_color(data, x, y);
			draw_tile_pixels(data, x, y, color);
		}
	}
}

void	init_minimap(t_data *data)
{
	int	w;
	int	h;

	data->minimap.tile = 8;
	data->minimap.x = 10;
	data->minimap.y = 10;
	w = data->map_width * data->minimap.tile;
	h = data->map_height * data->minimap.tile;
	data->minimap.img = mlx_new_image(data->mlx, w, h);
	if (!data->minimap.img)
		return ;
	data->minimap.addr = mlx_get_data_addr(data->minimap.img,
			&data->minimap.bpp, &data->minimap.len, &data->minimap.endian);
	data->minimap.view_w = 180;
	data->minimap.view_h = 180;
	data->minimap.view_img = mlx_new_image(data->mlx, data->minimap.view_w,
			data->minimap.view_h);
	if (data->minimap.view_img)
		data->minimap.view_addr = mlx_get_data_addr(data->minimap.view_img,
				&data->minimap.view_bpp, &data->minimap.view_len,
				&data->minimap.view_endian);
}

void	draw_minimap(t_data *data)
{
	int	px;
	int	py;

	if (!data->minimap.addr)
		return ;
	draw_minimap_helper(data);
	px = (int)(data->player_x * data->minimap.tile);
	py = (int)(data->player_y * data->minimap.tile);
	draw_player_dot(data, px, py);
}

void	draw_miniview(t_data *data)
{
	t_norm	norm;

	if (!data->minimap.addr)
		return ;
	norm.start_px = (int)(data->player_x * data->minimap.tile)
		- data->minimap.view_w / 2;
	norm.start_py = (int)(data->player_y * data->minimap.tile)
		- data->minimap.view_h / 2;
	norm.dst_off_x = data->minimap.x;
	norm.dst_off_y = data->minimap.y;
	draw_miniview_pixels(data, &norm);
	draw_player_marker(data, norm.dst_off_x, norm.dst_off_y);
}
