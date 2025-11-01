/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:33 by letto             #+#    #+#             */
/*   Updated: 2025/11/01 19:13:14 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_walkable_char(char c)
{
	return (c == '0' || is_player_character(c));
}

static int	is_blocking_char(char c)
{
	return (c == '1' || c == 'D');
}

void	flood_fill(t_flood_context *ctx, int x, int y)
{
	char	current;

	if (x < 0 || y < 0 || x >= ctx->map_width || y >= ctx->map_height)
		ft_error_exit_with_cleanup("Player can escape from map boundaries",
			EXIT_FAILURE, ctx->data, ctx->content);
	if (ctx->visited[y][x])
		return ;
	current = get_map_char_safe(ctx->map_lines, x, y, ctx->map_height);
	if (is_blocking_char(current))
		return ;
	if (!is_valid_walkable_char(current))
		return ;
	ctx->visited[y][x] = 1;
	check_boundary_conditions(ctx, x, y);
	flood_fill(ctx, x + 1, y);
	flood_fill(ctx, x - 1, y);
	flood_fill(ctx, x, y + 1);
	flood_fill(ctx, x, y - 1);
}

int	**allocate_visited_array(int map_width, int map_height, t_data *data,
		t_file_content *content)
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
	t_flood_context	ctx;

	init_flood_context(&ctx, map_lines, data, content);
}
