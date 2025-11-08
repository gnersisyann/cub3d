/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:40:16 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:26:41 by ganersis         ###   ########.fr       */
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

int	validate_texture_path(char *path)
{
	int	fd;

	if (!path)
		return (0);
	ft_check_file_extension(path, ".xpm", 0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	validate_color_component(char *component)
{
	int		value;
	int		i;
	char	*trimmed;

	if (!component)
		return (0);
	trimmed = ft_trim_whitespace(component);
	if (!trimmed || !*trimmed)
		return (0);
	i = 0;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
			return (0);
		i++;
	}
	value = ft_atoi(trimmed);
	return (value >= 0 && value <= 255);
}
