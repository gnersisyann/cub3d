/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:15:59 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/27 11:48:34 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mouse(t_data *data)
{
	data->last_mouse_x = -1;
	data->last_mouse_y = -1;
	data->mouse_captured = 1;
	data->pitch = 0.0;
}

static int	wrap_mouse_position(t_data *data, int *x, int *y)
{
	int	warped;

	warped = 0;
	if (*x > WIDTH - MOUSE_WRAP)
	{
		*x = MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->win, *x, *y);
		warped = 1;
	}
	else if (*x < MOUSE_WRAP)
	{
		*x = WIDTH - MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->win, *x, *y);
		warped = 1;
	}
	return (warped);
}

static void	rotate_with_angle(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	if (angle == 0.0)
		return ;
	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		warped;
	int		delta_x;
	double	angle;

	(void)y;
	if (!data->mouse_captured)
		return (0);
	warped = wrap_mouse_position(data, &x, &y);
	if (warped)
	{
		data->last_mouse_x = x;
		return (0);
	}
	if (data->last_mouse_x == -1)
	{
		data->last_mouse_x = x;
		return (0);
	}
	delta_x = x - data->last_mouse_x;
	if (delta_x != 0)
	{
		angle = delta_x * MOUSE_SENSITIVITY;
		rotate_with_angle(data, angle);
	}
	return (data->last_mouse_x = x, 0);
}

void	toggle_mouse_capture(t_data *data)
{
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	data->last_mouse_x = WIDTH / 2;
	data->last_mouse_y = HEIGHT / 2;
}
