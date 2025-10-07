#include "cub3d.h"

void	process_miniview_pixel(t_data *data, t_coords *coords)
{
	coords->src = data->minimap.addr + coords->src_y * data->minimap.len
		+ coords->src_x * (data->minimap.bpp / 8);
	coords->color = *(int *)coords->src;
	if (coords->color != 0xFF000000)
	{
		coords->pixel.x = coords->screen_x;
		coords->pixel.y = coords->screen_y;
		coords->pixel.color = coords->color;
		put_pixel_with_struct(&coords->pixel);
	}
}

int	check_miniview_bounds(t_data *data, t_coords *coords)
{
	return (coords->src_x >= 0 && coords->src_y >= 0
		&& coords->src_x < data->map_width * data->minimap.tile
		&& coords->src_y < data->map_height * data->minimap.tile);
}

void	draw_tile_pixels(t_data *data, int x, int y, int color)
{
	int		px;
	int		py;
	t_pixel	pixel;

	pixel.addr = data->minimap.addr;
	pixel.len = data->minimap.len;
	pixel.bpp = data->minimap.bpp;
	pixel.color = color;
	py = -1;
	while (++py < data->minimap.tile)
	{
		px = -1;
		while (++px < data->minimap.tile)
		{
			pixel.x = x * data->minimap.tile + px;
			pixel.y = y * data->minimap.tile + py;
			put_pixel_raw(&pixel);
		}
	}
}

void	draw_player_dot(t_data *data, int px, int py)
{
	int		x;
	int		y;
	t_pixel	pixel;

	pixel.addr = data->minimap.addr;
	pixel.len = data->minimap.len;
	pixel.bpp = data->minimap.bpp;
	pixel.color = 0x00FF0000;
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
