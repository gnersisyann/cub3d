/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_continuity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:49:07 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 17:53:10 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "validation.h"
#include <stdlib.h>

static int	check_remaining_lines(t_continuity_context *ctx, int start_pos)
{
	int	j;

	j = start_pos;
	while (ctx->lines[j])
	{
		if (is_potential_map_line(ctx->lines[j]))
		{
			ft_error_exit_with_cleanup("Map contains disconnected parts",
				EXIT_FAILURE, ctx->data, ctx->content);
			return (0);
		}
		if (!is_empty_line(ctx->lines[j]))
		{
			ft_error_exit_with_cleanup("Invalid content found after map",
				EXIT_FAILURE, ctx->data, ctx->content);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	handle_empty_line(t_continuity_context *ctx, int i,
		int *found_map_end)
{
	if (*found_map_end == 0)
	{
		if (!check_remaining_lines(ctx, i + 1))
			return (0);
		*found_map_end = 1;
	}
	return (1);
}

int	validate_map_continuity(char **lines, int map_start_index, t_data *data,
		t_file_content *content)
{
	int						i;
	int						found_map_end;
	t_continuity_context	ctx;

	ctx.lines = lines;
	ctx.data = data;
	ctx.content = content;
	i = map_start_index - 1;
	found_map_end = 0;
	while (lines[++i])
	{
		if (is_potential_map_line(lines[i]))
		{
			if (found_map_end)
				return (ft_error_exit_with_cleanup("Map contains \
			disconnected parts", EXIT_FAILURE, data, content), 0);
		}
		else if (!is_empty_line(lines[i]))
			return (ft_error_exit_with_cleanup("Invalid content \
		found in map section", EXIT_FAILURE, data, content), 0);
		else if (!handle_empty_line(&ctx, i, &found_map_end))
			return (0);
	}
	return (1);
}
