/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:33 by letto             #+#    #+#             */
/*   Updated: 2025/11/17 00:16:12 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    
    if (is_boundary_violation(current))
        ft_error_exit_with_cleanup("Map is not closed by walls - found hole in boundary",
            EXIT_FAILURE, ctx->data, ctx->content);
    
    if (is_blocking_char(current))
        return ;
    if (current == 'D')
    {
        check_boundary_for_doors(ctx, x, y, current);
        return ;
    }
    if (!is_valid_walkable_char(current))
        return ;
    check_boundary_for_doors(ctx, x, y, current);
    ctx->visited[y][x] = 1;
    flood_fill(ctx, x + 1, y);
    flood_fill(ctx, x - 1, y);
    flood_fill(ctx, x, y + 1);
    flood_fill(ctx, x, y - 1);
}

void	validate_map_closure(char **map_lines, t_data *data,
        t_file_content *content)
{
    t_flood_context	ctx;
    char			**normalized_map;
    int				map_width;
    int				map_height;
    int				i;

    map_width = get_map_width(map_lines);
    map_height = get_map_height(map_lines);
    
    normalized_map = normalize_map_with_boundaries(map_lines, map_width, map_height);
    if (!normalized_map)
        ft_error_exit_with_cleanup("Failed to normalize map", EXIT_FAILURE, data, content);
    
    init_flood_context(&ctx, normalized_map, data, content);
    
    i = 0;
    while (i < map_height)
    {
        free(normalized_map[i]);
        i++;
    }
    free(normalized_map);
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

