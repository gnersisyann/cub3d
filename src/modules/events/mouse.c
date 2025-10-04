#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void	init_mouse(t_data *data)
{
	data->last_mouse_x = -1;
	data->last_mouse_y = -1;
	data->mouse_captured = 1;
	data->pitch = 0.0;
}

int	mouse_move(int x, int y, t_data *data)
{
	double	rotation_angle;
	int		center_x;
	int		center_y;

	int delta_x, delta_y;
	double old_dir_x, old_plane_x;
	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	if (!data->mouse_captured)
		return (0);
	delta_x = x - center_x;
	delta_y = y - center_y;
	if (abs(delta_x) > 5 || abs(delta_y) > 5)
	{
		mlx_mouse_move(data->mlx, data->win, center_x, center_y);
		if (delta_x != 0)
		{
			rotation_angle = delta_x * MOUSE_SENSITIVITY;
			old_dir_x = data->dir_x;
			old_plane_x = data->plane_x;
			data->dir_x = data->dir_x * cos(rotation_angle) - data->dir_y
				* sin(rotation_angle);
			data->dir_y = old_dir_x * sin(rotation_angle) + data->dir_y
				* cos(rotation_angle);
			data->plane_x = data->plane_x * cos(rotation_angle) - data->plane_y
				* sin(rotation_angle);
			data->plane_y = old_plane_x * sin(rotation_angle) + data->plane_y
				* cos(rotation_angle);
		}
		if (delta_y != 0)
		{
			data->pitch += delta_y * MOUSE_SENSITIVITY;
			if (data->pitch > M_PI / 3)
				data->pitch = M_PI / 3;
			if (data->pitch < -M_PI / 3)
				data->pitch = -M_PI / 3;
		}
	}
	return (0);
}

void	toggle_mouse_capture(t_data *data)
{
	data->mouse_captured = !data->mouse_captured;
}
