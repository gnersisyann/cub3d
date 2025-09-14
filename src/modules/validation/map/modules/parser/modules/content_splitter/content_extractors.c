/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_extractors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:44:14 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:45:23 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"
#include <stdlib.h>

char	**extract_config_lines(char **lines, int map_start_index, t_data *data,
		t_file_content *content)
{
	char	**config_lines;
	int		config_count;
	int		i;
	int		j;

	config_count = 0;
	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
			config_count++;
		i++;
	}
	config_lines = (char **)malloc(sizeof(char *) * (config_count + 1));
	if (!config_lines)
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	j = 0;
	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
		{
			config_lines[j] = ft_strdup(lines[i]);
			if (!config_lines[j])
			{
				while (j > 0)
					free(config_lines[--j]);
				free(config_lines);
				ft_error_exit_with_cleanup("Memory allocation failed",
					EXIT_FAILURE, data, content);
			}
			j++;
		}
		i++;
	}
	config_lines[j] = NULL;
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

char	**extract_map_lines(char **lines, int map_start_index, t_data *data,
		t_file_content *content)
{
	char	**map_lines;
	int		map_count;
	int		i;
	int		j;
	char	*normalized_line;

	map_count = 0;
	i = map_start_index;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
			map_count++;
		i++;
	}
	if (map_count == 0)
		ft_error_exit_with_cleanup("No valid map found in file", EXIT_FAILURE,
			data, content);
	map_lines = (char **)malloc(sizeof(char *) * (map_count + 1));
	if (!map_lines)
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	j = 0;
	i = map_start_index;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			normalized_line = normalize_map_line(lines[i]);
			if (!normalized_line)
			{
				while (j > 0)
					free(map_lines[--j]);
				free(map_lines);
				ft_error_exit_with_cleanup("Memory allocation failed",
					EXIT_FAILURE, data, content);
			}
			map_lines[j] = normalized_line;
			j++;
		}
		i++;
	}
	map_lines[j] = NULL;
	return (map_lines);
}
