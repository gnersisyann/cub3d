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
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
}

static void	process_config_line(char *line, t_data *data,
		t_file_content *content)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture_line(line, &data->north_texture, data, content);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture_line(line, &data->south_texture, data, content);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture_line(line, &data->west_texture, data, content);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture_line(line, &data->east_texture, data, content);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color_line(line, &data->floor_color, data, content);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color_line(line, &data->ceiling_color, data, content);
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
