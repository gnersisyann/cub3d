/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:44:44 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:46:41 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"
#include <stdlib.h>

void	ft_split_file_content(char **lines, t_file_content *content,
		t_data *data)
{
	int	map_start_index;
	int	has_config;

	if (!lines || !lines[0])
	{
		ft_free_array(lines);
		ft_error_exit_with_cleanup("Invalid input", EXIT_FAILURE, data,
			content);
	}
	validate_all_lines(lines, data, content);
	map_start_index = find_map_start_index(lines, data, content);
	if (map_start_index == -2)
	{
		ft_free_array(lines);
		ft_error_exit_with_cleanup("Configuration elements found after map start",
			EXIT_FAILURE, data, content);
	}
	if (map_start_index == -1)
	{
		ft_free_array(lines);
		ft_error_exit_with_cleanup("No map found in file", EXIT_FAILURE, data,
			content);
	}
	has_config = check_has_config(lines, map_start_index);
	if (!has_config)
	{
		ft_free_array(lines);
		ft_error_exit_with_cleanup("No configuration elements found",
			EXIT_FAILURE, data, content);
	}
	content->config_lines = extract_config_lines(lines, map_start_index, data,
			content);
	if (!content->config_lines)
	{
		ft_free_array(lines);
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	}
	content->map_lines = extract_map_lines(lines, map_start_index, data,
			content);
	if (!content->map_lines)
	{
		ft_free_array(content->config_lines);
		content->config_lines = NULL;
		ft_free_array(lines);
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	}
}
