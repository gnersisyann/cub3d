/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 19:47:39 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(char c)
{
	return (c == '1');
}

static int	check_horizontal_walls(char **map, int x, int y, int height)
{
	char	left;
	char	right;

	left = get_map_char_safe(map, x - 1, y, height);
	right = get_map_char_safe(map, x + 1, y, height);
	return (is_wall(left) && is_wall(right));
}

static int	check_vertical_walls(char **map, int x, int y, int height)
{
	char	top;
	char	bottom;

	top = get_map_char_safe(map, x, y - 1, height);
	bottom = get_map_char_safe(map, x, y + 1, height);
	return (is_wall(top) && is_wall(bottom));
}

static void	validate_single_door(char **map, int x, int y, t_door_val_ctx *ctx)
{
	int	horizontal_ok;
	int	vertical_ok;

	horizontal_ok = check_horizontal_walls(map, x, y, ctx->map_height);
	vertical_ok = check_vertical_walls(map, x, y, ctx->map_height);
	if (!horizontal_ok && !vertical_ok)
		ft_error_exit_with_cleanup("Door must \
be enclosed by walls on two sides",
			EXIT_FAILURE, ctx->data, ctx->content);
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
