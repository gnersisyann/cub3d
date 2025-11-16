/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:48:24 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/17 00:12:41 by letto            ###   ########.fr       */
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
