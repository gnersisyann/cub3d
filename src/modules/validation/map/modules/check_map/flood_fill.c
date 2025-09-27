/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:33 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:58:03 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"
#include <stdlib.h>

char	get_map_char_safe(char **map_lines, int x, int y, int map_height)
{
	int	line_len;

	if (y < 0 || y >= map_height || x < 0)
		return ('1');
	line_len = ft_strlen(map_lines[y]);
	if (map_lines[y][line_len - 1] == '\n')
		line_len--;
	if (x >= line_len)
		return ('1');
	return (map_lines[y][x]);
}

static void	flood_fill_recursive(char **map_lines, int x, int y, int map_width,
		int map_height, int **visited, t_data *data, t_file_content *content)
{
	char	current;

	if (x < 0 || y < 0 || x >= map_width || y >= map_height)
		ft_error_exit_with_cleanup("Player can escape from map boundaries",
			EXIT_FAILURE, data, content);
	if (visited[y][x])
		return ;
	current = get_map_char_safe(map_lines, x, y, map_height);
	if (current == '1')
		return ;
	if (current != '0' && !is_player_character(current))
		return ;
	visited[y][x] = 1;
	if (x == 0 || y == 0 || x >= map_width - 1 || y >= map_height - 1)
	{
		if (current == '0' || is_player_character(current))
			ft_error_exit_with_cleanup("Map is not closed by walls",
				EXIT_FAILURE, data, content);
	}
	flood_fill_recursive(map_lines, x + 1, y, map_width, map_height, visited,
		data, content);
	flood_fill_recursive(map_lines, x - 1, y, map_width, map_height, visited,
		data, content);
	flood_fill_recursive(map_lines, x, y + 1, map_width, map_height, visited,
		data, content);
	flood_fill_recursive(map_lines, x, y - 1, map_width, map_height, visited,
		data, content);
}

static int	**allocate_visited_array(int map_width, int map_height,
		t_data *data, t_file_content *content)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(sizeof(int *) * map_height);
	if (!visited)
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	i = 0;
	while (i < map_height)
	{
		visited[i] = (int *)ft_calloc(map_width, sizeof(int));
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
				data, content);
		}
		i++;
	}
	return (visited);
}

void	validate_map_closure(char **map_lines, t_data *data,
		t_file_content *content)
{
	int	map_width;
	int	map_height;
	int	player_count;
	int	player_x;
	int	player_y;
	int	**visited;
	int	i;

	map_width = get_map_width(map_lines);
	map_height = get_map_height(map_lines);
	find_player_position(map_lines, &player_count, &player_x, &player_y);
	visited = allocate_visited_array(map_width, map_height, data, content);
	flood_fill_recursive(map_lines, player_x, player_y, map_width, map_height,
		visited, data, content);
	i = 0;
	while (i < map_height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
