/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:43:23 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:43:47 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t' || c == '\n');
}

int	is_config_identifier(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i + 1])
	{
		if ((line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
			|| (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			|| (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			|| (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' '))
			return (1);
	}
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (1);
	return (0);
}

int	is_potential_map_line(char *line)
{
	int	i;
	int	has_map_content;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (is_config_identifier(line))
		return (0);
	has_map_content = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_map_character(line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			has_map_content = 1;
		i++;
	}
	return (has_map_content);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
