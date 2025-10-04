/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:06:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 18:06:58 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "stdlib.h"
#include "error.h"

void	check_boundary_conditions(t_flood_context *ctx, int x, int y)
{
	char	current;

	if (x < 0 || y < 0 || x >= ctx->map_width || y >= ctx->map_height)
		ft_error_exit_with_cleanup("Player can escape from map boundaries",
			EXIT_FAILURE, ctx->data, ctx->content);
	current = get_map_char_safe(ctx->map_lines, x, y, ctx->map_height);
	if (x == 0 || y == 0 || x >= ctx->map_width - 1 || y >= ctx->map_height - 1)
		if (current == '0' || is_player_character(current))
			ft_error_exit_with_cleanup("Map is not closed by walls",
				EXIT_FAILURE, ctx->data, ctx->content);
}

void	cleanup_visited_array(int **visited, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	init_flood_context(t_flood_context *ctx, char **map_lines, t_data *data,
		t_file_content *content)
{
	int	player_count;
	int	player_x;
	int	player_y;

	ctx->map_lines = map_lines;
	ctx->map_width = get_map_width(map_lines);
	ctx->map_height = get_map_height(map_lines);
	ctx->data = data;
	ctx->content = content;
	find_player_position(map_lines, &player_count, &player_x, &player_y);
	ctx->visited = allocate_visited_array(ctx->map_width, ctx->map_height, data,
			content);
	flood_fill_recursive(ctx, player_x, player_y);
	cleanup_visited_array(ctx->visited, ctx->map_height);
}
