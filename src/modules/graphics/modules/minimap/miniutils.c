#include "cub3d.h"

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

int	get_minimap_color(t_data *data, int map_x, int map_y)
{
	char	c;
	int		line_len;

	if (map_y < 0 || map_y >= data->map_height || map_x < 0
		|| map_x >= data->map_width)
		return (0xFF000000);
	if (!data->map[map_y])
		return (0xFF000000);
	line_len = ft_strlen(data->map[map_y]);
	if (map_x >= line_len)
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
