/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:56:46 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 17:56:46 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "libft.h"
#include "error.h"

int	count_config_lines(char **lines, int map_start_index)
{
	int	config_count;
	int	i;

	config_count = 0;
	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
			config_count++;
		i++;
	}
	return (config_count);
}

void	cleanup_config_lines(char **config_lines, int j)
{
	while (j > 0)
		free(config_lines[--j]);
	free(config_lines);
}

void	fill_config_lines(t_line_fill_context *ctx,
		t_extraction_context *ext_ctx)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < ext_ctx->map_start_index)
	{
		if (is_config_identifier(ctx->lines[i]))
		{
			ctx->target_lines[j] = ft_strdup(ctx->lines[i]);
			if (!ctx->target_lines[j])
			{
				cleanup_config_lines(ctx->target_lines, j);
				ft_error_exit_with_cleanup("Memory allocation failed",
					EXIT_FAILURE, ext_ctx->data, ext_ctx->content);
			}
			j++;
		}
		i++;
	}
	ctx->target_lines[j] = NULL;
}

int	validate_no_config_after_map(char **lines, int map_start_index,
		t_data *data, t_file_content *content)
{
	int	i;

	i = map_start_index;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_config_identifier(lines[i]))
			return (0);
		if (!is_empty_line(lines[i]))
			ft_error_exit_with_cleanup("Invalid content found after map start",
				EXIT_FAILURE, data, content);
		i++;
	}
	return (1);
}
