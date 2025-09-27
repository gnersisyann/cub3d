/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_continuity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:00:00 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:44:10 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "validation.h"
#include <stdlib.h>

int	validate_map_continuity(char **lines, int map_start_index, t_data *data,
		t_file_content *content)
{
	int	i;
	int	found_map_end;
	int	j;

	i = map_start_index;
	found_map_end = 0;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			if (found_map_end)
			{
				ft_error_exit_with_cleanup("Map contains disconnected parts",
					EXIT_FAILURE, data, content);
				return (0);
			}
		}
		else if (!is_empty_line(lines[i]))
		{
			ft_error_exit_with_cleanup("Invalid content found in map section",
				EXIT_FAILURE, data, content);
			return (0);
		}
		else if (found_map_end == 0)
		{
			j = i + 1;
			while (lines[j])
			{
				if (is_potential_map_line(lines[j]))
				{
					ft_error_exit_with_cleanup("Map contains disconnected parts",
						EXIT_FAILURE, data, content);
					return (0);
				}
				if (!is_empty_line(lines[j]))
				{
					ft_error_exit_with_cleanup("Invalid content found after map",
						EXIT_FAILURE, data, content);
					return (0);
				}
				j++;
			}
			found_map_end = 1;
		}
		i++;
	}
	return (1);
}
