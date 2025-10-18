/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:52:44 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:59:53 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_data(t_file_content *content, t_data *data)
{
	int	player_count;
	int	player_x;
	int	player_y;

	find_player_position(content->map_lines, &player_count, &player_x,
		&player_y);
	data->player_x = (double)player_x + 0.5;
	data->player_y = (double)player_y + 0.5;
	data->player_direction = content->map_lines[player_y][player_x];
}

static void	set_map_dimensions(t_file_content *content, t_data *data)
{
	data->map_width = get_map_width(content->map_lines);
	data->map_height = get_map_height(content->map_lines);
}

static void	duplicate_map_data(t_file_content *content, t_data *data)
{
	data->map = ft_duplicate_map(content->map_lines, data->map_height);
	if (!data->map)
		ft_error_exit_with_cleanup("Failed to duplicate map", EXIT_FAILURE,
			data, content);
}

void	ft_validate_map_structure(t_file_content *content, t_data *data)
{
	if (!content || !content->map_lines)
		ft_error_exit_with_cleanup("No map data to validate", EXIT_FAILURE,
			data, content);
	validate_map_size(content->map_lines, data, content);
	validate_map_characters(content->map_lines, data, content);
	validate_player_count(content->map_lines, data, content);
	validate_map_closure(content->map_lines, data, content);
	set_player_data(content, data);
	set_map_dimensions(content, data);
	duplicate_map_data(content, data);
}
