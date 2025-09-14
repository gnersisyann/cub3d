/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:31 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:28:31 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include <fcntl.h>

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

int	validate_color_component(char *component)
{
	int	value;
	int	i;

	if (!component)
		return (0);
	i = 0;
	while (component[i])
	{
		if (!ft_isdigit(component[i]))
			return (0);
		i++;
	}
	value = ft_atoi(component);
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

int	validate_all_configs(t_data *data)
{
	if (!data->north_texture || !data->south_texture || !data->west_texture
		|| !data->east_texture)
		return (0);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (0);
	return (1);
}
