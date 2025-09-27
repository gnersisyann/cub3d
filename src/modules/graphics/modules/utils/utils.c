#include "cub3d.h"
#include "defines.h"
#include "graphics.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	clear_screen(t_data *data)
{
    int	total_pixels;
    int	i;

    total_pixels = WIDTH * HEIGHT;
    i = 0;
    while (i < total_pixels)
    {
        ((unsigned int*)data->addr)[i] = 0;
        i++;
    }
}

void	draw_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(data, x, y, data->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(data, x, y, data->floor_color);
			x++;
		}
		y++;
	}
}
