/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:34:34 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:36:06 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	file_line_count(char *filename, t_data *data,
		t_file_content *content)
{
	size_t	count;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error_exit_with_cleanup("Cannot open file", EXIT_FAILURE, data,
			content);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

char	**parse_file(char *filename, t_data *data, t_file_content *content)
{
	int		fd;
	size_t	line_count;
	char	**result;
	size_t	i;

	line_count = file_line_count(filename, data, content);
	if (line_count == 0)
		ft_error_exit_with_cleanup("File is empty", EXIT_FAILURE, data,
			content);
	result = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!result)
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(result);
		ft_error_exit_with_cleanup("Cannot open file", EXIT_FAILURE, data,
			content);
	}
	i = 0;
	while (i < line_count)
	{
		result[i] = get_next_line(fd);
		if (!result[i])
			break ;
		i++;
	}
	result[i] = NULL;
	close(fd);
	return (result);
}
