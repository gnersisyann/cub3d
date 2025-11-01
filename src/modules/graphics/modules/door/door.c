/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:35:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/01 16:33:23 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ✅ Подсчитывает количество дверей на карте
static int	count_doors_in_map(t_data *data)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

// ✅ Инициализирует массив дверей из карты
void	init_doors(t_data *data)
{
	int	y;
	int	x;
	int	door_index;

	data->door_count = count_doors_in_map(data);
	if (data->door_count == 0)
		return ;
	data->doors = malloc(sizeof(t_door) * data->door_count);
	if (!data->doors)
		return ;
	door_index = 0;
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'D')
			{
				data->doors[door_index].map_x = x;
				data->doors[door_index].map_y = y;
				data->doors[door_index].open_offset = 0.0;
				data->doors[door_index].is_opening = 0;
				data->doors[door_index].is_closing = 0;
				data->doors[door_index].is_open = 0;
				door_index++;
			}
		}
	}
}

// ✅ Получает дверь по координатам карты
t_door	*get_door_at_position(t_data *data, int map_x, int map_y)
{
	int	i;

	if (!data->doors)
		return (NULL);
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].map_x == map_x && data->doors[i].map_y == map_y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

// ✅ Проверяет расстояние игрока до двери и открывает/закрывает
void	check_door_proximity(t_data *data)
{
	int		i;
	double	dist_x;
	double	dist_y;
	double	distance;

	if (!data->doors)
		return ;
	i = 0;
	while (i < data->door_count)
	{
		dist_x = data->player_x - (data->doors[i].map_x + 0.5);
		dist_y = data->player_y - (data->doors[i].map_y + 0.5);
		distance = sqrt(dist_x * dist_x + dist_y * dist_y);
		if (distance < DOOR_OPEN_DISTANCE)
		{
			if (!data->doors[i].is_open && !data->doors[i].is_opening)
				data->doors[i].is_opening = 1;
		}
		else
		{
			if (data->doors[i].is_open && !data->doors[i].is_closing)
				data->doors[i].is_closing = 1;
		}
		i++;
	}
}

// ✅ Обновляет состояние всех дверей (анимация)
void	update_doors(t_data *data, double delta_time)
{
	int	i;

	if (!data->doors)
		return ;
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].is_opening)
		{
			data->doors[i].open_offset += DOOR_OPEN_SPEED * delta_time;
			if (data->doors[i].open_offset >= 1.0)
			{
				data->doors[i].open_offset = 1.0;
				data->doors[i].is_opening = 0;
				data->doors[i].is_open = 1;
			}
		}
		else if (data->doors[i].is_closing)
		{
			data->doors[i].open_offset -= DOOR_OPEN_SPEED * delta_time;
			if (data->doors[i].open_offset <= 0.0)
			{
				data->doors[i].open_offset = 0.0;
				data->doors[i].is_closing = 0;
				data->doors[i].is_open = 0;
			}
		}
		i++;
	}
}
