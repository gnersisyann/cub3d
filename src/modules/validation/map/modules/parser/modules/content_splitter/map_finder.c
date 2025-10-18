/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:44:35 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:56:30 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_all_lines(char **lines, t_data *data, t_file_content *content)
{
	int		i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		if (!is_config_identifier(line) && !is_potential_map_line(line)
			&& !is_empty_line(line))
		{
			ft_error_exit_with_cleanup("Invalid content found in file",
				EXIT_FAILURE, data, content);
		}
		i++;
	}
}

int	find_map_start_index(char **lines, t_data *data, t_file_content *content)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			if (validate_no_config_after_map(lines, i, data, content))
				return (i);
			else
				return (-2);
		}
		i++;
	}
	return (-1);
}

int	check_has_config(char **lines, int map_start_index)
{
	int	i;

	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
			return (1);
		i++;
	}
	return (0);
}

void	cleanup_map_lines(char **map_lines, int j)
{
	while (j > 0)
		free(map_lines[--j]);
	free(map_lines);
}
