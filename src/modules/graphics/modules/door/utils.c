/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:20:50 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/01 19:33:46 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door(t_data *data, int door_index, int x, int y)
{
	data->doors[door_index].map_x = x;
	data->doors[door_index].map_y = y;
	data->doors[door_index].open_offset = 0.0;
	data->doors[door_index].is_opening = 0;
	data->doors[door_index].is_closing = 0;
	data->doors[door_index].is_open = 0;
}

void	set_door_status(t_door *doors, bool is_open, int i)
{
	if (is_open)
	{
		doors[i].open_offset = 1.0;
		doors[i].is_opening = 0;
		doors[i].is_open = 1;
	}
	else
	{
		doors[i].open_offset = 0.0;
		doors[i].is_closing = 0;
		doors[i].is_open = 0;
	}
}
