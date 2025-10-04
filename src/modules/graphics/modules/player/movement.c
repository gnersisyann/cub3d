/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:36:28 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 18:11:11 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "defines.h"
#include "graphics.h"

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

void	move_right(t_data *data)
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

void	move_left(t_data *data)
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
