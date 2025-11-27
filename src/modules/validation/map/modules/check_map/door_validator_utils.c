/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validator_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:30:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/27 13:30:00 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(char c)
{
	return (c == '1');
}

int	is_walkable_space(char c)
{
	return (c == '0' || c == 'L' || is_player_character(c));
}

char	get_door_char(char **map, int x, int y, int height)
{
	int	line_len;

	if (y < 0 || y >= height || x < 0)
		return (' ');
	line_len = ft_strlen(map[y]);
	if (x >= line_len)
		return (' ');
	return (map[y][x]);
}

int	check_horizontal_walls(char **map, int x, int y, int height)
{
	char	left;
	char	right;

	left = get_door_char(map, x - 1, y, height);
	right = get_door_char(map, x + 1, y, height);
	return (is_wall(left) && is_wall(right));
}

int	check_vertical_walls(char **map, int x, int y, int height)
{
	char	top;
	char	bottom;

	top = get_door_char(map, x, y - 1, height);
	bottom = get_door_char(map, x, y + 1, height);
	return (is_wall(top) && is_wall(bottom));
}
