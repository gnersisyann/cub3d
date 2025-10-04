/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_extractors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:48:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 17:56:39 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"
#include <stdlib.h>

char	**extract_config_lines(t_extraction_context *ctx)
{
	char				**config_lines;
	int					config_count;
	t_line_fill_context	fill_ctx;

	config_count = count_config_lines(ctx->lines, ctx->map_start_index);
	config_lines = (char **)malloc(sizeof(char *) * (config_count + 1));
	if (!config_lines)
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			ctx->data, ctx->content);
	fill_ctx.lines = ctx->lines;
	fill_ctx.target_lines = config_lines;
	fill_ctx.start_index = 0;
	fill_ctx.count = config_count;
	fill_config_lines(&fill_ctx, ctx);
	return (config_lines);
}

static char	*normalize_map_line(char *line)
{
	char	*normalized;
	int		i;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	normalized = (char *)malloc(sizeof(char) * (len + 1));
	if (!normalized)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			normalized[i] = '0';
		else
			normalized[i] = line[i];
		i++;
	}
	normalized[i] = '\0';
	return (normalized);
}

static int	count_map_lines(char **lines, int map_start_index)
{
	int	map_count;
	int	i;

	map_count = 0;
	i = map_start_index;
	while (lines[i] && is_potential_map_line(lines[i]))
	{
		map_count++;
		i++;
	}
	return (map_count);
}

static void	fill_map_lines(t_line_fill_context *ctx,
		t_extraction_context *ext_ctx)
{
	int		j;
	int		i;
	char	*normalized_line;

	j = 0;
	i = ctx->start_index;
	while (ctx->lines[i] && is_potential_map_line(ctx->lines[i])
		&& j < ctx->count)
	{
		normalized_line = normalize_map_line(ctx->lines[i]);
		if (!normalized_line)
		{
			cleanup_map_lines(ctx->target_lines, j);
			ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
				ext_ctx->data, ext_ctx->content);
		}
		ctx->target_lines[j] = normalized_line;
		j++;
		i++;
	}
	ctx->target_lines[j] = NULL;
}

char	**extract_map_lines(t_extraction_context *ctx)
{
	char				**map_lines;
	int					map_count;
	t_line_fill_context	fill_ctx;

	map_count = count_map_lines(ctx->lines, ctx->map_start_index);
	if (map_count == 0)
		ft_error_exit_with_cleanup("No valid map found in file", EXIT_FAILURE,
			ctx->data, ctx->content);
	map_lines = (char **)malloc(sizeof(char *) * (map_count + 1));
	if (!map_lines)
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			ctx->data, ctx->content);
	fill_ctx.lines = ctx->lines;
	fill_ctx.target_lines = map_lines;
	fill_ctx.start_index = ctx->map_start_index;
	fill_ctx.count = map_count;
	fill_map_lines(&fill_ctx, ctx);
	return (map_lines);
}
