/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:49:03 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 17:50:43 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_input(t_extraction_context *ctx)
{
	if (!ctx->lines || !ctx->lines[0])
	{
		ft_free_array(ctx->lines);
		ft_error_exit_with_cleanup("Invalid input", EXIT_FAILURE, ctx->data,
			ctx->content);
	}
}

static int	get_map_start_index(t_extraction_context *ctx)
{
	int	map_start_index;

	map_start_index = find_map_start_index(ctx->lines, ctx->data, ctx->content);
	if (map_start_index == -2)
	{
		ft_free_array(ctx->lines);
		ft_error_exit_with_cleanup("Configuration elements found after \
            map start", EXIT_FAILURE, ctx->data, ctx->content);
	}
	if (map_start_index == -1)
	{
		ft_free_array(ctx->lines);
		ft_error_exit_with_cleanup("No map found in file", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
	return (map_start_index);
}

static void	validate_configuration(t_extraction_context *ctx)
{
	int	has_config;

	has_config = check_has_config(ctx->lines, ctx->map_start_index);
	if (!has_config)
	{
		ft_free_array(ctx->lines);
		ft_error_exit_with_cleanup("No configuration elements found",
			EXIT_FAILURE, ctx->data, ctx->content);
	}
}

static void	extract_content_parts(t_extraction_context *ctx)
{
	ctx->content->config_lines = extract_config_lines(ctx);
	if (!ctx->content->config_lines)
	{
		ft_free_array(ctx->lines);
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
	ctx->content->map_lines = extract_map_lines(ctx);
	if (!ctx->content->map_lines)
	{
		ft_free_array(ctx->content->config_lines);
		ctx->content->config_lines = NULL;
		ft_free_array(ctx->lines);
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
}

void	ft_split_file_content(char **lines, t_file_content *content,
		t_data *data)
{
	t_extraction_context	ctx;

	ctx.lines = lines;
	ctx.data = data;
	ctx.content = content;
	validate_input(&ctx);
	validate_all_lines(ctx.lines, ctx.data, ctx.content);
	ctx.map_start_index = get_map_start_index(&ctx);
	validate_map_continuity(ctx.lines, ctx.map_start_index, ctx.data,
		ctx.content);
	validate_configuration(&ctx);
	extract_content_parts(&ctx);
}
