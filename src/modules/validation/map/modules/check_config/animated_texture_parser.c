/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_texture_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:30:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:21:13 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**extract_all_paths_from_line(char *line, int *count)
{
	char	**paths;
	char	*path_start;
	char	*trimmed_line;

	path_start = line;
	while (*path_start && *path_start != ' ' && *path_start != '\t')
		path_start++;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	if (!*path_start)
		return (*count = 0, NULL);
	trimmed_line = ft_strtrim(path_start, " \t\n");
	if (!trimmed_line || !*trimmed_line)
	{
		if (trimmed_line)
			free(trimmed_line);
		return (*count = 0, NULL);
	}
	paths = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!paths)
		return (*count = 0, NULL);
	*count = 0;
	while (paths[*count])
		(*count)++;
	return (paths);
}

static char	*validate_and_trim_path(char *path, t_texture_context *ctx,
		char **paths)
{
	char	*trimmed_path;

	trimmed_path = ft_strtrim(path, " \t\n");
	if (!trimmed_path || !*trimmed_path)
	{
		if (trimmed_path)
			free(trimmed_path);
		return (NULL);
	}
	if (!validate_texture_path(trimmed_path))
	{
		free(trimmed_path);
		ft_free_array(paths);
		ft_error_exit_with_cleanup("Invalid texture path", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
	return (trimmed_path);
}

static char	**realloc_texture_array(char ***texture_paths, int *texture_count,
		char *new_path, t_texture_context *ctx)
{
	char	**new_array;
	int		j;

	new_array = malloc(sizeof(char *) * (*texture_count + 1));
	if (!new_array)
	{
		free(new_path);
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
	j = 0;
	while (j < *texture_count)
	{
		new_array[j] = (*texture_paths)[j];
		j++;
	}
	new_array[*texture_count] = new_path;
	if (*texture_paths)
		free(*texture_paths);
	return (new_array);
}

static void	process_single_path(char **paths, int i, t_path_process *proc)
{
	char	*trimmed_path;

	if (!paths[i] || !*paths[i])
		return ;
	trimmed_path = validate_and_trim_path(paths[i], proc->ctx, paths);
	if (!trimmed_path)
		return ;
	*proc->texture_paths = realloc_texture_array(proc->texture_paths,
			proc->texture_count, trimmed_path, proc->ctx);
	(*proc->texture_count)++;
}

static void	process_all_paths(char **paths, int path_count,
		t_path_process *proc)
{
	int	i;

	i = 0;
	while (i < path_count)
	{
		process_single_path(paths, i, proc);
		i++;
	}
}

void	parse_animated_texture_line(char *line, char ***texture_paths,
		int *texture_count, t_texture_context *ctx)
{
	char			**paths;
	int				path_count;
	t_path_process	proc;

	paths = extract_all_paths_from_line(line, &path_count);
	if (!paths || path_count == 0)
	{
		if (paths)
			ft_free_array(paths);
		ft_error_exit_with_cleanup("Missing texture path", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
	proc.texture_paths = texture_paths;
	proc.texture_count = texture_count;
	proc.ctx = ctx;
	process_all_paths(paths, path_count, &proc);
	if (*texture_count == 0)
	{
		ft_free_array(paths);
		ft_error_exit_with_cleanup("No valid texture paths found", EXIT_FAILURE,
			ctx->data, ctx->content);
	}
	ft_free_array(paths);
}
