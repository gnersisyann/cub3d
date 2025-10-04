/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:02 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:59:58 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_player_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	find_player_position(char **map_lines, int *player_count, int *player_x,
		int *player_y)
{
	int	i;
	int	j;

	*player_count = 0;
	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (is_player_character(map_lines[i][j]))
			{
				(*player_count)++;
				*player_x = j;
				*player_y = i;
			}
			j++;
		}
		i++;
	}
}

int	get_map_width(char **map_lines)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (map_lines[i])
	{
		current_width = ft_strlen(map_lines[i]);
		if (map_lines[i][current_width - 1] == '\n')
			current_width--;
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	get_map_height(char **map_lines)
{
	int	height;

	height = 0;
	while (map_lines[height])
		height++;
	return (height);
}
