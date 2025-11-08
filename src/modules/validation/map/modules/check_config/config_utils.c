/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:40:16 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 17:40:17 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_path_from_line(char *line)
{
	char	*path_start;
	char	*texture_path;

	path_start = line;
	while (*path_start && *path_start != ' ' && *path_start != '\t')
		path_start++;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	if (!*path_start)
		return (NULL);
	texture_path = ft_strtrim(path_start, " \t\n");
	return (texture_path);
}
