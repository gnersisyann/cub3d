#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include "mlx.h"

void	init_raw_data(t_pixel *px, t_data *data)
{
	px->addr = data->addr;
	px->len = data->line_length;
	px->bpp = data->bits_per_pixel;
}

void	put_pixel_with_struct(t_pixel *px)
{
	char	*dst;

	dst = px->addr + px->y * px->len + px->x * (px->bpp / 8);
	*(int *)dst = px->color;
}

void	put_pixel_raw(t_pixel *px)
{
	char	*dst;

	dst = px->addr + px->y * px->len + px->x * (px->bpp / 8);
	*(int *)dst = px->color;
}

void	draw_player_marker(t_data *data, int dst_off_x, int dst_off_y)
{
	int	cx;
	int	cy;
	int	dy;
	int	dx;
	t_pixel	pixel;

	cx = dst_off_x + data->minimap.view_w / 2;
	cy = dst_off_y + data->minimap.view_h / 2;
	init_raw_data(&pixel, data);
	pixel.color = 0x00FF0000; // RED
	dy = -3;
	while (++dy <= 2)
	{
		dx = -3;
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

int	get_minimap_color(t_data *data, int map_x, int map_y)
{
	char	c;

	if (map_y < 0 || map_y >= data->map_height || map_x < 0
		|| map_x >= data->map_width)
		return (0xFF000000);
	if (!data->map[map_y])
		return (0xFF000000);
	c = data->map[map_y][map_x];
	if (c == '1')
		return (0x008BB5F8);
	if (c == '0')
		return (0x005E5C64);
	if (c == ' ')
		return (0xFF000000);
	return (0x005E5C64);
}
