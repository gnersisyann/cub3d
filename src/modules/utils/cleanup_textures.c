/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:31:44 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:12:05 by ganersis         ###   ########.fr       */
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

static void	cleanup_lamp_textures(t_data *data)
{
	int	i;

	if (data->lamp_textures)
	{
		i = 0;
		while (i < data->lamp_texture_count)
		{
			if (data->lamp_textures[i])
				free(data->lamp_textures[i]);
			i++;
		}
		free(data->lamp_textures);
		data->lamp_textures = NULL;
		data->lamp_texture_count = 0;
	}
	if (data->animated_lamp_texture.frames)
	{
		if (data->mlx)
		{
			i = 0;
			while (i < data->animated_lamp_texture.frame_count)
			{
				if (data->animated_lamp_texture.frames[i].img)
					mlx_destroy_image(data->mlx,
						data->animated_lamp_texture.frames[i].img);
				i++;
			}
		}
		free(data->animated_lamp_texture.frames);
		data->animated_lamp_texture.frames = NULL;
	}
	data->animated_lamp_texture.frame_count = 0;
}

void	cleanup_texture_arrays(t_data *data)
{
	cleanup_north_south_textures(data);
	cleanup_west_east_textures(data);
	cleanup_door_textures(data);
	cleanup_lamp_textures(data);
}
