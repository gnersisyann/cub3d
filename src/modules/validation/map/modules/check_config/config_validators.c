/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:31 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 18:25:23 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_texture_path(char *path)
{
	int	fd;

	if (!path)
		return (0);
	ft_check_file_extension(path, ".xpm", 0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	map_has_lamps(char **map_lines)
{
	int	i;
	int	j;

	if (!map_lines)
		return (0);
	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (map_lines[i][j] == 'L')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	validate_lamp_texture_consistency(t_data *data, t_file_content *content)
{
	int	has_lamps_on_map;
	int	has_lamp_texture;

	has_lamps_on_map = map_has_lamps(content->map_lines);
	has_lamp_texture = (data->lamp_textures != NULL
			&& data->lamp_texture_count > 0);
	if (has_lamps_on_map && !has_lamp_texture)
		ft_error_exit_with_cleanup("Map contains lamps (L)\
 but no lamp texture (LA) is defined",
									EXIT_FAILURE,
									data,
									content);
	if (!has_lamps_on_map && has_lamp_texture)
		ft_error_exit_with_cleanup("Lamp texture (LA) is d\
efined but no lamps (L) found on map",
									EXIT_FAILURE,
									data,
									content);
}

int	validate_color_component(char *component)
{
	int		value;
	int		i;
	char	*trimmed;

	if (!component)
		return (0);
	trimmed = ft_trim_whitespace(component);
	if (!trimmed || !*trimmed)
		return (0);
	i = 0;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
			return (0);
		i++;
	}
	value = ft_atoi(trimmed);
	return (value >= 0 && value <= 255);
}

int	validate_color_line(char *line)
{
	char	**components;
	int		result;

	components = ft_split(line, ',');
	if (!components)
		return (0);
	if (!components[0] || !components[1] || !components[2] || components[3])
	{
		ft_free_array(components);
		return (0);
	}
	result = validate_color_component(components[0])
		&& validate_color_component(components[1])
		&& validate_color_component(components[2]);
	ft_free_array(components);
	return (result);
}

void	validate_door_texture_consistency(t_data *data, t_file_content *content)
{
	int	has_doors_on_map;
	int	has_door_texture;

	has_doors_on_map = map_has_doors(content->map_lines);
	has_door_texture = (data->door_textures != NULL
			&& data->door_texture_count > 0);
	if (has_doors_on_map && !has_door_texture)
		ft_error_exit_with_cleanup("Map contains doors (D)\
 but no door texture (DO) is defined",
									EXIT_FAILURE,
									data,
									content);
	if (!has_doors_on_map && has_door_texture)
		ft_error_exit_with_cleanup("Door texture (DO) is d\
efined but no doors (D) found on map",
									EXIT_FAILURE,
									data,
									content);
}

int	validate_all_configs(t_data *data)
{
	if (!data->north_textures || data->north_texture_count == 0
		|| !data->south_textures || data->south_texture_count == 0
		|| !data->west_textures || data->west_texture_count == 0
		|| !data->east_textures || data->east_texture_count == 0)
		return (0);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (0);
	return (1);
}
