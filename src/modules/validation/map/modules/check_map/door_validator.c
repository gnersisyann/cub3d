/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/27 12:24:56 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_perpendicular_spaces(char first, char second,
		t_door_val_ctx *ctx)
{
	if (!is_walkable_space(first) || !is_walkable_space(second))
		ft_error_exit_with_cleanup("Door must connect two walkable spaces",
			EXIT_FAILURE, ctx->data, ctx->content);
}

static void	ensure_not_on_boundary(char **map, int x, int y,
		t_door_val_ctx *ctx)
{
	int	line_len;

	if (y == 0 || y == ctx->map_height - 1)
		ft_error_exit_with_cleanup("Door on map boundary - map not closed",
			EXIT_FAILURE, ctx->data, ctx->content);
	line_len = ft_strlen(map[y]);
	if (x == 0 || x >= line_len - 1)
		ft_error_exit_with_cleanup("Door on map boundary - map not closed",
			EXIT_FAILURE, ctx->data, ctx->content);
}

static void	validate_single_door(char **map, int x, int y, t_door_val_ctx *ctx)
{
	int		horizontal_ok;
	int		vertical_ok;
	char	first;
	char	second;

	ensure_not_on_boundary(map, x, y, ctx);
	horizontal_ok = check_horizontal_walls(map, x, y, ctx->map_height);
	vertical_ok = check_vertical_walls(map, x, y, ctx->map_height);
	if (!horizontal_ok && !vertical_ok)
		ft_error_exit_with_cleanup("Door must \
be enclosed by walls on two sides",
			EXIT_FAILURE, ctx->data, ctx->content);
	if (horizontal_ok)
	{
		first = get_door_char(map, x, y - 1, ctx->map_height);
		second = get_door_char(map, x, y + 1, ctx->map_height);
	}
	else
	{
		first = get_door_char(map, x - 1, y, ctx->map_height);
		second = get_door_char(map, x + 1, y, ctx->map_height);
	}
	validate_perpendicular_spaces(first, second, ctx);
}

void	validate_all_doors(char **map, t_data *data, t_file_content *content)
{
	t_door_val_ctx	ctx;
	int				y;
	int				x;

	ctx.map_height = get_map_height(map);
	ctx.data = data;
	ctx.content = content;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
				validate_single_door(map, x, y, &ctx);
			x++;
		}
		y++;
	}
}
