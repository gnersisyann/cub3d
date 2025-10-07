/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:40 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:29:28 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"

static char	*extract_path_from_line(char *line)
{
	char	*path_start;
	char	*texture_path;

	path_start = line + 2;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	if (!*path_start)
		return (NULL);
	texture_path = ft_strtrim(path_start, " \t\n");
	return (texture_path);
}

void	parse_texture_line(char *line, char **texture_path, t_data *data,
		t_file_content *content)
{
	if (*texture_path)
		ft_error_exit_with_cleanup("Duplicate texture identifier", EXIT_FAILURE,
			data, content);
	*texture_path = extract_path_from_line(line);
	if (!*texture_path)
		ft_error_exit_with_cleanup("Missing texture path", EXIT_FAILURE, data,
			content);
	if (!validate_texture_path(*texture_path))
		ft_error_exit_with_cleanup("Invalid texture path", EXIT_FAILURE, data,
			content);
}

static int	create_color_value(char **components)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(components[0]);
	green = ft_atoi(components[1]);
	blue = ft_atoi(components[2]);
	return ((red << 16) | (green << 8) | blue);
}

void	parse_color_line(char *line, int *color, t_data *data,
		t_file_content *content)
{
	char	*color_start;
	char	**components;

	if (*color != -1)
		ft_error_exit_with_cleanup("Duplicate color identifier", EXIT_FAILURE,
			data, content);
	color_start = line + 1;
	while (*color_start && (*color_start == ' ' || *color_start == '\t'))
		color_start++;
	if (!*color_start)
		ft_error_exit_with_cleanup("Missing color values", EXIT_FAILURE, data,
			content);
	color_start = ft_strtrim(color_start, " \t\n");
	if (!validate_color_line(color_start))
	{
		free(color_start);
		ft_error_exit_with_cleanup("Invalid color format", EXIT_FAILURE, data,
			content);
	}
	components = ft_split(color_start, ',');
	*color = create_color_value(components);
	ft_free_array(components);
	free(color_start);
}

void	parse_animated_texture_line(char *line, char ***texture_paths,
		int *texture_count, t_data *data, t_file_content *content)
{
	char	*new_path;
	char	**new_array;
	int		i;

	new_path = extract_path_from_line(line);
	if (!new_path)
		ft_error_exit_with_cleanup("Missing texture path", EXIT_FAILURE, data,
			content);
	if (!validate_texture_path(new_path))
	{
		free(new_path);
		ft_error_exit_with_cleanup("Invalid texture path", EXIT_FAILURE, data,
			content);
	}
	new_array = malloc(sizeof(char *) * (*texture_count + 1));
	if (!new_array)
	{
		free(new_path);
		ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
			data, content);
	}
	i = -1;
	while (++i < *texture_count)
		new_array[i] = (*texture_paths)[i];
	new_array[*texture_count] = new_path;
	if (*texture_paths)
		free(*texture_paths);
	*texture_paths = new_array;
	(*texture_count)++;
}
