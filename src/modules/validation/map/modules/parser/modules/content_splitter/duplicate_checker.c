/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 15:14:22 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static char	*extract_texture_path(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*path;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	ft_strlcpy(path, &line[start], len + 1);
	return (path);
}

static char	*extract_identifier(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*identifier;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	identifier = (char *)malloc(sizeof(char) * (len + 1));
	if (!identifier)
		return (NULL);
	ft_strlcpy(identifier, &line[start], len + 1);
	return (identifier);
}

static int	is_texture_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i + 1])
	{
		if ((line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' '
					|| line[i + 2] == '\t')) || (line[i] == 'S' && line[i
					+ 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
			|| (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' '
					|| line[i + 2] == '\t')) || (line[i] == 'E' && line[i
					+ 1] == 'A' && (line[i + 2] == ' ' || line[i + 2] == '\t')))
			return (1);
	}
	return (0);
}

static void	check_same_identifier_duplicates(char *path1, char *id1,
		t_dup_ctx *ctx, int start_j)
{
	int		j;
	char	*path2;
	char	*id2;

	j = start_j - 1;
	while (ctx->config_lines[++j])
	{
		if (is_texture_line(ctx->config_lines[j]))
		{
			id2 = extract_identifier(ctx->config_lines[j]);
			if (id2 && ft_strcmp(id1, id2) == 0)
			{
				path2 = extract_texture_path(ctx->config_lines[j]);
				if (path2 && ft_strcmp(path1, path2) == 0)
				{
					free(path2);
					free(id2);
					ft_error_exit_with_cleanup("Duplicate texture path found",
						EXIT_FAILURE, ctx->data, ctx->content);
				}
				free(path2);
			}
			free(id2);
		}
	}
}

void	validate_texture_duplicates(char **config_lines, t_data *data,
		t_file_content *content)
{
	int			i;
	char		*path1;
	char		*id1;
	t_dup_ctx	ctx;

	ctx.config_lines = config_lines;
	ctx.data = data;
	ctx.content = content;
	i = 0;
	while (config_lines[i])
	{
		if (is_texture_line(config_lines[i]))
		{
			path1 = extract_texture_path(config_lines[i]);
			id1 = extract_identifier(config_lines[i]);
			if (path1 && id1)
				check_same_identifier_duplicates(path1, id1, &ctx, i + 1);
			free(path1);
			free(id1);
		}
		i++;
	}
}
