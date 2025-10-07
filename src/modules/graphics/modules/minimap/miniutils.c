#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

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

static void	draw_fov_120(t_data *data, int cx, int cy, t_pixel *pixel)
{
	int		angle;
	int		radius;
	int		x;
	int		y;
	double	rad;
	double	player_angle;

	player_angle = atan2(data->dir_y, data->dir_x);
	pixel->color = 0xF0D3D3;
	radius = 1;
	while (radius <= 20)
	{
		angle = -60;
		while (angle <= 60)
		{
			rad = player_angle + (angle * M_PI / 180.0);
			x = cx + (int)(radius * cos(rad));
			y = cy + (int)(radius * sin(rad));
			pixel->x = x;
			pixel->y = y;
			if (pixel->x >= 0 && pixel->x < WIDTH && pixel->y >= 0
				&& pixel->y < HEIGHT)
				put_pixel_with_struct(pixel);
			angle += 1;
		}
		radius++;
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
