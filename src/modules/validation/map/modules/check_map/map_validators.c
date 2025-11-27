/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:18 by letto             #+#    #+#             */
/*   Updated: 2025/11/17 00:21:07 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_player_count(char **map_lines, t_data *data,
		t_file_content *content)
{
	int	player_count;
	int	player_x;
	int	player_y;

	find_player_position(map_lines, &player_count, &player_x, &player_y);
	if (player_count == 0)
		ft_error_exit_with_cleanup("No player found in map", EXIT_FAILURE, data,
			content);
	if (player_count > 1)
		ft_error_exit_with_cleanup("Multiple players found in map",
			EXIT_FAILURE, data, content);
}

char	**normalize_map_with_boundaries(char **map_lines, int map_width,
		int map_height)
{
	char	**normalized_map;
	int		i;

	normalized_map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (!normalized_map)
		return (NULL);
	i = 0;
	while (i < map_height)
	{
		normalized_map[i] = (char *)malloc(sizeof(char) * (map_width + 1));
		if (!normalized_map[i])
		{
			while (i > 0)
				free(normalized_map[--i]);
			free(normalized_map);
			return (NULL);
		}
		normalize_map_line(map_lines[i], normalized_map[i], map_width);
		i++;
	}
	normalized_map[map_height] = NULL;
	return (normalized_map);
}

void	validate_map_characters(char **map_lines, t_data *data,
		t_file_content *content)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			c = map_lines[i][j];
			if (c != '0' && c != '1' && !is_player_character(c) && c != '\n'
				&& c != 'D' && c != 'L' && c != ' ')
			{
				ft_error_exit_with_cleanup("Invalid character in map",
					EXIT_FAILURE, data, content);
			}
			j++;
		}
		i++;
	}
}

void	validate_map_size(char **map_lines, t_data *data,
		t_file_content *content)
{
	int	height;
	int	width;

	height = get_map_height(map_lines);
	width = get_map_width(map_lines);
	if (height < 3 || width < 3)
		ft_error_exit_with_cleanup("Map is too small", EXIT_FAILURE, data,
			content);
}

char	**ft_duplicate_map(char **map_lines, int height)
{
	char	**new_map;
	int		i;
	int		len;

	new_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_map[i] = ft_strdup(map_lines[i]);
		if (!new_map[i])
		{
			while (i > 0)
				free(new_map[--i]);
			free(new_map);
			return (NULL);
		}
		len = ft_strlen(new_map[i]);
		if (len > 0 && new_map[i][len - 1] == '\n')
			new_map[i][len - 1] = '\0';
		i++;
	}
	new_map[height] = NULL;
	return (new_map);
}
