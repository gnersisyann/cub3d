/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:31:44 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/01 19:18:11 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_north_south_textures(t_data *data)
{
	int	i;

	if (data->north_textures)
	{
		i = -1;
		while (++i < data->north_texture_count)
		{
			if (data->north_textures[i])
				free(data->north_textures[i]);
		}
		free(data->north_textures);
		data->north_textures = NULL;
	}
	if (data->south_textures)
	{
		i = -1;
		while (++i < data->south_texture_count)
		{
			if (data->south_textures[i])
				free(data->south_textures[i]);
		}
		free(data->south_textures);
		data->south_textures = NULL;
	}
}

static void	cleanup_west_east_textures(t_data *data)
{
	int	i;

	if (data->west_textures)
	{
		i = -1;
		while (++i < data->west_texture_count)
		{
			if (data->west_textures[i])
				free(data->west_textures[i]);
		}
		free(data->west_textures);
		data->west_textures = NULL;
	}
	if (data->east_textures)
	{
		i = -1;
		while (++i < data->east_texture_count)
		{
			if (data->east_textures[i])
				free(data->east_textures[i]);
		}
		free(data->east_textures);
		data->east_textures = NULL;
	}
}

static void	cleanup_door_textures(t_data *data)
{
	int	i;

	if (data->door_textures)
	{
		i = -1;
		while (++i < data->door_texture_count)
		{
			if (data->door_textures[i])
				free(data->door_textures[i]);
		}
		free(data->door_textures);
		data->door_textures = NULL;
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
	cleanup_door_textures(data);
}
