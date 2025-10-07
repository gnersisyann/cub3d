/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:49 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:29:24 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"

static void	init_config_data(t_data *data)
{
	data->north_textures = NULL;
	data->south_textures = NULL;
	data->west_textures = NULL;
	data->east_textures = NULL;
	data->north_texture_count = 0;
	data->south_texture_count = 0;
	data->west_texture_count = 0;
	data->east_texture_count = 0;
	data->floor_color = -1;
	data->ceiling_color = -1;
}

static void	process_config_line(char *line, t_data *data,
		t_file_content *content)
{
	char	*trimmed_line;

	trimmed_line = ft_skip_whitespace(line);
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
		parse_animated_texture_line(trimmed_line, &data->north_textures,
			&data->north_texture_count, data, content);
	else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
		parse_animated_texture_line(trimmed_line, &data->south_textures,
			&data->south_texture_count, data, content);
	else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
		parse_animated_texture_line(trimmed_line, &data->west_textures,
			&data->west_texture_count, data, content);
	else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
		parse_animated_texture_line(trimmed_line, &data->east_textures,
			&data->east_texture_count, data, content);
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		parse_color_line(trimmed_line, &data->floor_color, data, content);
	else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		parse_color_line(trimmed_line, &data->ceiling_color, data, content);
	else
		ft_error_exit_with_cleanup("Unknown configuration identifier",
			EXIT_FAILURE, data, content);
}

static void	parse_all_config_lines(t_file_content *content, t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	while (content->config_lines[i])
	{
		line = content->config_lines[i];
		if (!line || !line[0] || line[0] == '\n')
		{
			i++;
			continue ;
		}
		process_config_line(line, data, content);
		i++;
	}
}

void	ft_check_config(t_file_content *content, t_data *data)
{
	init_config_data(data);
	if (!content->config_lines)
		ft_error_exit_with_cleanup("No configuration found", EXIT_FAILURE, data,
			content);
	parse_all_config_lines(content, data);
	if (!validate_all_configs(data))
		ft_error_exit_with_cleanup("Missing configuration", EXIT_FAILURE, data,
			content);
}
