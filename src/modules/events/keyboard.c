/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:57 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:11:57 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "events.h"
#include "graphics.h"
#include <math.h>
#include <stdio.h>

static void	move_forward(t_data *data)
{
	double	new_x, new_y;
	double	move_speed = 0.015;

	new_x = data->player_x + data->dir_x * move_speed;
	new_y = data->player_y + data->dir_y * move_speed;

	// Check if new position is valid (not a wall)
	if (new_x >= 0 && new_x < data->map_width && new_y >= 0 && new_y < data->map_height
		&& data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

static void	move_backward(t_data *data)
{
	double	new_x, new_y;
	double	move_speed = 0.015;

	new_x = data->player_x - data->dir_x * move_speed;
	new_y = data->player_y - data->dir_y * move_speed;

	// Check if new position is valid (not a wall)
	if (new_x >= 0 && new_x < data->map_width && new_y >= 0 && new_y < data->map_height
		&& data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

static void	strafe_left(t_data *data)
{
	double	new_x, new_y;
	double	move_speed = 0.03;

	new_x = data->player_x - data->plane_x * move_speed;
	new_y = data->player_y - data->plane_y * move_speed;

	// Check if new position is valid (not a wall)
	if (new_x >= 0 && new_x < data->map_width &&
		new_y >= 0 && new_y < data->map_height &&
		data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

static void	strafe_right(t_data *data)
{
	double	new_x, new_y;
	double	move_speed = 0.03;

	new_x = data->player_x + data->plane_x * move_speed;
	new_y = data->player_y + data->plane_y * move_speed;

	// Check if new position is valid (not a wall)
	if (new_x >= 0 && new_x < data->map_width &&
		new_y >= 0 && new_y < data->map_height &&
		data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
}

static void	rotate_right(t_data *data)
{
	double	rot_speed = 0.02;
	double	old_dir_x = data->dir_x;
	double	old_plane_x = data->plane_x;

	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
	data->plane_x = data->plane_x * cos(rot_speed) - data->plane_y * sin(rot_speed);
	data->plane_y = old_plane_x * sin(rot_speed) + data->plane_y * cos(rot_speed);
}

static void	rotate_left(t_data *data)
{
	double	rot_speed = -0.02;
	double	old_dir_x = data->dir_x;
	double	old_plane_x = data->plane_x;

	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
	data->plane_x = data->plane_x * cos(rot_speed) - data->plane_y * sin(rot_speed);
	data->plane_y = old_plane_x * sin(rot_speed) + data->plane_y * cos(rot_speed);
}

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == 119)  // W key
		data->key_w = 1;
	else if (keycode == 115)  // S key
		data->key_s = 1;
	else if (keycode == 97)   // A key
		data->key_a = 1;
	else if (keycode == 100)  // D key
		data->key_d = 1;
	else if (keycode == 65361)  // Left arrow
		data->key_left = 1;
	else if (keycode == 65363)  // Right arrow
		data->key_right = 1;
	else if (keycode == 65307)  // ESC key
		ft_exit(data);
	
	data->needs_redraw = 1;
	return (0);
}

int	ft_key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->key_w = 0;
	else if (keycode == S)
		data->key_s = 0;
	else if (keycode == A)
		data->key_a = 0;
	else if (keycode == D)
		data->key_d = 0;
	else if (keycode == LARROW)
		data->key_left = 0;
	else if (keycode == RARROW)
		data->key_right = 0;
	
	return (0);
}

void	process_movement(t_data *data)
{
	int moved = 0;
	
	if (data->key_w)
	{
		move_forward(data);
		moved = 1;
	}
	if (data->key_s)
	{
		move_backward(data);
		moved = 1;
	}
	if (data->key_a)
	{
		strafe_left(data);
		moved = 1;
	}
	if (data->key_d)
	{
		strafe_right(data);
		moved = 1;
	}
	if (data->key_left)
	{
		rotate_left(data);
		moved = 1;
	}
	if (data->key_right)
	{
		rotate_right(data);
		moved = 1;
	}
	
	if (moved)
		data->needs_redraw = 1;
}