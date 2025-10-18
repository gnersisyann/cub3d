/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   required_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 15:13:47 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	line_starts_with_identifier(char *line, char *id)
{
	int	i;
	int	j;
	int	id_len;

	if (!line || !id)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	id_len = ft_strlen(id);
	j = 0;
	while (j < id_len && line[i + j] == id[j])
		j++;
	if (j == id_len && (line[i + j] == ' ' || line[i + j] == '\t'))
		return (1);
	return (0);
}

static void	check_identifier_presence(t_dup_ctx *ctx, char *id)
{
	int	i;

	i = 0;
	while (ctx->config_lines[i])
	{
		if (line_starts_with_identifier(ctx->config_lines[i], id))
			return ;
		i++;
	}
	ft_error_exit_with_cleanup("Missing required configuration identifier",
		EXIT_FAILURE, ctx->data, ctx->content);
}

void	validate_required_identifiers(char **config_lines, t_data *data,
		t_file_content *content)
{
	t_dup_ctx	ctx;

	ctx.config_lines = config_lines;
	ctx.data = data;
	ctx.content = content;
	check_identifier_presence(&ctx, "NO");
	check_identifier_presence(&ctx, "SO");
	check_identifier_presence(&ctx, "WE");
	check_identifier_presence(&ctx, "EA");
	check_identifier_presence(&ctx, "F");
	check_identifier_presence(&ctx, "C");
}

void	validate_no_duplicates(char **config_lines, t_data *data,
		t_file_content *content)
{
	validate_required_identifiers(config_lines, data, content);
	validate_texture_duplicates(config_lines, data, content);
}
