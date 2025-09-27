#include "cub3d.h"
#include "defines.h"
#include "graphics.h"
#include <math.h>

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x + data->dir_x * MOVE_SPEED;
	new_y = data->player_y + data->dir_y * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x - data->dir_x * MOVE_SPEED;
	new_y = data->player_y - data->dir_y * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x - data->dir_y * MOVE_SPEED;
	new_y = data->player_y + data->dir_x * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player_x + data->dir_y * MOVE_SPEED;
	new_y = data->player_y - data->dir_x * MOVE_SPEED;
	if (data->map[(int)data->player_y][(int)new_x] != '1')
		data->player_x = new_x;
	if (data->map[(int)new_y][(int)data->player_x] != '1')
		data->player_y = new_y;
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED) - data->dir_y * sin(ROT_SPEED);
	data->dir_y = old_dir_x * sin(ROT_SPEED) + data->dir_y * cos(ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED) - data->plane_y
		* sin(ROT_SPEED);
	data->plane_y = old_plane_x * sin(ROT_SPEED) + data->plane_y
		* cos(ROT_SPEED);
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-ROT_SPEED) - data->dir_y * sin(-ROT_SPEED);
	data->dir_y = old_dir_x * sin(-ROT_SPEED) + data->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-ROT_SPEED) - data->plane_y
		* sin(-ROT_SPEED);
	data->plane_y = old_plane_x * sin(-ROT_SPEED) + data->plane_y
		* cos(-ROT_SPEED);
}
