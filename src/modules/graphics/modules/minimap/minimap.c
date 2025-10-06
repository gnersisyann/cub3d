#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include "mlx.h"

// TODO: Needs to Norminette draw_miiview_pixels() and draw_minimap_helper functions karch asac alareci

static void	draw_miniview_pixels(t_data *data, t_norm *norm)
{
	int		y;
	int		x;
	int		screen_y;
	int		screen_x;
	int		src_x;
	int		src_y;
	char	*src;
	int		color;
	t_pixel	pixel;

	init_raw_data(&pixel, data);
	y = -1;
	while (++y < data->minimap.view_h)
	{
		screen_y = norm->dst_off_y + y;
		if (screen_y < 0 || screen_y >= HEIGHT)
			continue ;
		x = -1;
		while (++x < data->minimap.view_w)
		{
			screen_x = norm->dst_off_x + x;
			if (screen_x < 0 || screen_x >= WIDTH)
				continue ;
			src_x = norm->start_px + x;
			src_y = norm->start_py + y;
			if (src_x >= 0 && src_y >= 0 && src_x < data->map_width
				* data->minimap.tile && src_y < data->map_height
				* data->minimap.tile)
			{
				src = data->minimap.addr + src_y * data->minimap.len
					+ src_x * (data->minimap.bpp / 8);
				color = *(int *)src;
				if (color != 0xFF000000)
				{
					pixel.x = screen_x;
					pixel.y = screen_y;
					pixel.color = color;
					put_pixel_with_struct(&pixel);
				}
			}
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
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bpp,
			&data->minimap.len, &data->minimap.endian);
	data->minimap.view_w = 180;
	data->minimap.view_h = 180;
	data->minimap.view_img = mlx_new_image(data->mlx, data->minimap.view_w,
			data->minimap.view_h);
	if (data->minimap.view_img)
		data->minimap.view_addr = mlx_get_data_addr(data->minimap.view_img,
				&data->minimap.view_bpp, &data->minimap.view_len,
				&data->minimap.view_endian);
}
static void	draw_minimap_helper(t_data *data)
{
	int		x;
	int		y;
	int		color;
	int		px;
	int		py;
	t_pixel	pixel;

	pixel.addr = data->minimap.addr;
	pixel.len = data->minimap.len;
	pixel.bpp = data->minimap.bpp;
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			color = get_minimap_color(data, x, y);
			py = -1;
			while (++py < data->minimap.tile)
			{
				px = -1;
				while (++px < data->minimap.tile)
				{
					pixel.x = x * data->minimap.tile + px;
					pixel.y = y * data->minimap.tile + py;
					pixel.color = color;
					put_pixel_raw(&pixel);
				}
			}
		}
	}
}

void	draw_minimap(t_data *data)
{
	int		px;
	int		py;
	int		x;
	int		y;
	t_pixel	pixel;

	if (!data->minimap.addr)
		return ;
	draw_minimap_helper(data);
	pixel.addr = data->minimap.addr;
	pixel.len = data->minimap.len;
	pixel.bpp = data->minimap.bpp;
	pixel.color = 0x00FF0000;
	px = (int)(data->player_x * data->minimap.tile);
	py = (int)(data->player_y * data->minimap.tile);
	y = -3;
	while (++y <= 2)
	{
		x = -3;
		while (++x <= 2)
		{
			pixel.x = px + x;
			pixel.y = py + y;
			put_pixel_raw(&pixel);
		}
	}
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
