/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:34:21 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:34:24 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub_file(char *filename, t_file_content *content, t_data *data)
{
	char	**file_lines;

	file_lines = parse_file(filename, data, content);
	if (!file_lines)
		ft_error_exit_with_cleanup("Failed to parse file", EXIT_FAILURE, data,
			content);
	ft_split_file_content(file_lines, content, data);
	ft_free_array(file_lines);
}
