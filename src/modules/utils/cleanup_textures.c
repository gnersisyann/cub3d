/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:31:44 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:41:06 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture_paths(char **textures, int count)
{
	int	i;

	if (!textures)
		return ;
	i = 0;
	while (i < count)
	{
		if (textures[i])
			free(textures[i]);
		i++;
	}
	free(textures);
}

static void	cleanup_north_south_textures(t_data *data)
{
	if (data->north_textures)
	{
		free_texture_paths(data->north_textures, data->north_texture_count);
		data->north_textures = NULL;
	}
	if (data->south_textures)
	{
		free_texture_paths(data->south_textures, data->south_texture_count);
		data->south_textures = NULL;
	}
}

static void	cleanup_west_east_textures(t_data *data)
{
	if (data->west_textures)
	{
		free_texture_paths(data->west_textures, data->west_texture_count);
		data->west_textures = NULL;
	}
	if (data->east_textures)
	{
		free_texture_paths(data->east_textures, data->east_texture_count);
		data->east_textures = NULL;
	}
}

static void	cleanup_door_lamp_textures(t_data *data)
{
	if (data->door_textures)
	{
		free_texture_paths(data->door_textures, data->door_texture_count);
		data->door_textures = NULL;
	}
	if (data->lamp_textures)
	{
		free_texture_paths(data->lamp_textures, data->lamp_texture_count);
		data->lamp_textures = NULL;
	}
	if (data->doors)
	{
		free(data->doors);
		data->doors = NULL;
	}
}

void	cleanup_texture_arrays(t_data *data)
{
	cleanup_north_south_textures(data);
	cleanup_west_east_textures(data);
	cleanup_door_lamp_textures(data);
}
