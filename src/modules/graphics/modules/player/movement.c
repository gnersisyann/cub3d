/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:36:28 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/01 16:34:52 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_pass_through(t_data *data, int map_x, int map_y)
{
    t_door	*door;

    if (data->map[map_y][map_x] == '1')
        return (0);
    if (data->map[map_y][map_x] == 'D')
    {
        door = get_door_at_position(data, map_x, map_y);
        if (!door || door->open_offset < 0.5)
            return (0);
    }
    return (1);
}

void	move_forward(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player_x + data->dir_x * MOVE_SPEED;
    new_y = data->player_y + data->dir_y * MOVE_SPEED;
    if (can_pass_through(data, (int)new_x, (int)data->player_y))
        data->player_x = new_x;
    if (can_pass_through(data, (int)data->player_x, (int)new_y))
        data->player_y = new_y;
}

void	move_backward(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player_x - data->dir_x * MOVE_SPEED;
    new_y = data->player_y - data->dir_y * MOVE_SPEED;
    if (can_pass_through(data, (int)new_x, (int)data->player_y))
        data->player_x = new_x;
    if (can_pass_through(data, (int)data->player_x, (int)new_y))
        data->player_y = new_y;
}

void	move_right(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player_x - data->dir_y * MOVE_SPEED;
    new_y = data->player_y + data->dir_x * MOVE_SPEED;
    if (can_pass_through(data, (int)new_x, (int)data->player_y))
        data->player_x = new_x;
    if (can_pass_through(data, (int)data->player_x, (int)new_y))
        data->player_y = new_y;
}

void	move_left(t_data *data)
{
    double	new_x;
    double	new_y;

    new_x = data->player_x + data->dir_y * MOVE_SPEED;
    new_y = data->player_y - data->dir_x * MOVE_SPEED;
    if (can_pass_through(data, (int)new_x, (int)data->player_y))
        data->player_x = new_x;
    if (can_pass_through(data, (int)data->player_x, (int)new_y))
        data->player_y = new_y;
}
