/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:48:24 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/17 01:05:10 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_walkable_char(char c)
{
	return (c == '0' || is_player_character(c) || c == 'L');
}

int	is_blocking_char(char c)
{
	return (c == '1');
}

int	is_on_boundary(t_flood_context *ctx, int x, int y)
{
	return (x == 0 || y == 0 || x >= ctx->map_width - 1 || y >= ctx->map_height
		- 1);
}

int	is_boundary_violation(char c)
{
	return (c == '2');
}

int	validate_flood_position(t_flood_context *ctx, int x, int y, char current)
{
	if (x < 0 || y < 0 || x >= ctx->map_width || y >= ctx->map_height)
	{
		cleanup_visited_array(ctx->visited, ctx->map_height);
		cleanup_normalized_map(ctx->normalized_map, ctx->map_height);
		ft_error_exit_with_cleanup("Player can escape from map boundaries",
			EXIT_FAILURE, ctx->data, ctx->content);
	}
	if (ctx->visited[y][x])
		return (0);
	if (is_boundary_violation(current))
	{
		cleanup_visited_array(ctx->visited, ctx->map_height);
		cleanup_normalized_map(ctx->normalized_map, ctx->map_height);
		ft_error_exit_with_cleanup("Map is not closed by walls\
- found hole in boundary", EXIT_FAILURE, ctx->data, ctx->content);
	}
	if (is_blocking_char(current))
		return (0);
	return (1);
}
