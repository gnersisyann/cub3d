/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_texture_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:30:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 17:55:50 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**extract_all_paths_from_line(char *line, int *count)
{
	char	**paths;
	char	*path_start;

	path_start = line;
	while (*path_start && *path_start != ' ' && *path_start != '\t')
		path_start++;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	if (!*path_start)
	{
		*count = 0;
		return (NULL);
	}
	paths = ft_split(path_start, ' ');
	if (!paths)
	{
		*count = 0;
		return (NULL);
	}
	*count = 0;
	while (paths[*count])
		(*count)++;
	return (paths);
}

static void	process_all_paths(char **paths, int path_count,
		char ***texture_paths, int *texture_count, t_texture_context *ctx)
{
	int		i;
	char	*trimmed_path;
	char	**new_array;
	int		j;

	i = 0;
	while (i < path_count)
	{
		trimmed_path = ft_strtrim(paths[i], " \t\n");
		if (!trimmed_path || !*trimmed_path)
		{
			free(trimmed_path);
			ft_free_array(paths);
			ft_error_exit_with_cleanup("Empty texture path", EXIT_FAILURE,
				ctx->data, ctx->content);
		}
		if (!validate_texture_path(trimmed_path))
		{
			free(trimmed_path);
			ft_free_array(paths);
			ft_error_exit_with_cleanup("Invalid texture path", EXIT_FAILURE,
				ctx->data, ctx->content);
		}
		new_array = malloc(sizeof(char *) * (*texture_count + 1));
		if (!new_array)
		{
			free(trimmed_path);
			ft_free_array(paths);
			ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
				ctx->data, ctx->content);
		}
		j = 0;
		while (j < *texture_count)
		{
			new_array[j] = (*texture_paths)[j];
			j++;
		}
		new_array[*texture_count] = trimmed_path;
		if (*texture_paths)
			free(*texture_paths);
		*texture_paths = new_array;
		(*texture_count)++;
		i++;
	}
}

void	parse_animated_texture_line(char *line, char ***texture_paths,
		int *texture_count, t_texture_context *ctx)
{
	char **paths;
	int path_count;

	paths = extract_all_paths_from_line(line, &path_count);
	if (!paths || path_count == 0)
	{
		if (paths)
			ft_free_array(paths);
		ft_error_exit_with_cleanup("Missing texture path", EXIT_FAILURE,
			ctx->data, ctx->content);
	}

	process_all_paths(paths, path_count, texture_paths, texture_count, ctx);
	ft_free_array(paths);
}