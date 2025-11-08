/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:47:22 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:48:05 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_to_paths(char *line)
{
	char	*path_start;

	path_start = line;
	while (*path_start && *path_start != ' ' && *path_start != '\t')
		path_start++;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	return (path_start);
}

char	**extract_all_paths_from_line(char *line, int *count)
{
	char	**paths;
	char	*path_start;
	char	*trimmed_line;

	path_start = skip_to_paths(line);
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
