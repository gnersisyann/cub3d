/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:33 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 19:51:07 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_door_validation(t_flood_context *ctx, int x, int y);
static void	check_line_end_validation(t_flood_context *ctx, int x, int y);
static int	count_consecutive_zeros(t_flood_context *ctx, int x, int y);
static void	validate_door_line_end(t_flood_context *ctx, int line_len, int y);

static void	check_boundary_for_doors(t_flood_context *ctx, int x, int y,
		char current)
{
	if (is_on_boundary(ctx, x, y))
	{
		if (current == 'D')
			ft_error_exit_with_cleanup("Door on map boundary - map not closed",
				EXIT_FAILURE, ctx->data, ctx->content);
		if (current == '0' || is_player_character(current) || current == 'L')
			ft_error_exit_with_cleanup("Map is not closed by walls",
				EXIT_FAILURE, ctx->data, ctx->content);
	}
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
	if (current == 'D')
	{
		check_door_validation(ctx, x, y);
		return ;
	}
	if (!is_valid_walkable_char(current))
		return ;
	check_line_end_validation(ctx, x, y);
	check_boundary_for_doors(ctx, x, y, current);
	ctx->visited[y][x] = 1;
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

static void	check_door_validation(t_flood_context *ctx, int x, int y)
{
	int		line_len;
	int		consecutive_zeros;

	check_boundary_for_doors(ctx, x, y, 'D');
	line_len = ft_strlen(ctx->map_lines[y]);
	if (ctx->map_lines[y][line_len - 1] == '\n')
		line_len--;
	consecutive_zeros = count_consecutive_zeros(ctx, x, y);
	if (consecutive_zeros >= 3)
		validate_door_line_end(ctx, line_len, y);
}

static int	count_consecutive_zeros(t_flood_context *ctx, int x, int y)
{
	int	consecutive_zeros;
	int	check_x;
	int	line_len;

	consecutive_zeros = 0;
	check_x = x + 1;
	line_len = ft_strlen(ctx->map_lines[y]);
	if (ctx->map_lines[y][line_len - 1] == '\n')
		line_len--;
	while (check_x < line_len && get_map_char_safe(ctx->map_lines,
			check_x, y, ctx->map_height) == '0')
	{
		consecutive_zeros++;
		check_x++;
	}
	return (consecutive_zeros);
}

static void	validate_door_line_end(t_flood_context *ctx, int line_len, int y)
{
	char	last_char;

	last_char = get_map_char_safe(ctx->map_lines, line_len - 1,
			y, ctx->map_height);
	if (last_char != '1')
	{
		ft_error_exit_with_cleanup("Invalid map: door followed by "
			"walkable areas extending to line end without proper "
			"wall closure", EXIT_FAILURE, ctx->data, ctx->content);
	}
}

static void	check_line_end_validation(t_flood_context *ctx, int x, int y)
{
	int		line_len;
	char	last_char;

	line_len = ft_strlen(ctx->map_lines[y]);
	if (ctx->map_lines[y][line_len - 1] == '\n')
		line_len--;
	if (x >= line_len - 2)
	{
		last_char = get_map_char_safe(ctx->map_lines, line_len - 1,
				y, ctx->map_height);
		if (last_char != '1')
		{
			ft_error_exit_with_cleanup("Invalid map: walkable area extends "
				"to line end without wall closure", EXIT_FAILURE,
				ctx->data, ctx->content);
		}
	}
}
