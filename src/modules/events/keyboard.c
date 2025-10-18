/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:57 by letto             #+#    #+#             */
/*   Updated: 2025/10/18 18:51:49 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_exit(data);
	if (keycode == 101)
    {
        if (can_interact_with_door(data, data->player_x, data->player_y))
            interact_with_door(data->nearest_door);
    }
	else if (keycode < 65536)
		data->keys[keycode] = 1;
	return (0);
}

int	ft_key_release(int keycode, t_data *data)
{
	if (keycode < 65536)
		data->keys[keycode] = 0;
	return (0);
}

void	handle_movement(t_data *data)
{
	if (data->keys[W])
		move_forward(data);
	if (data->keys[S])
		move_backward(data);
	if (data->keys[A])
		move_left(data);
	if (data->keys[D])
		move_right(data);
	if (data->keys[LARROW])
		rotate_left(data);
	if (data->keys[RARROW])
		rotate_right(data);
}

int	ft_game_loop(t_data *data)
{
	handle_movement(data);
	ft_render_next_frame(data);
	return (0);
}
