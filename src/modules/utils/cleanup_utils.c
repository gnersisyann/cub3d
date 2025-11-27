/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:40:48 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_sprites(t_data *data)
{
	if (data->sprites)
	{
		free(data->sprites);
		data->sprites = NULL;
		data->sprite_count = 0;
	}
}

void	cleanup_buffers(t_data *data)
{
	if (data->z_buffer)
	{
		free(data->z_buffer);
		data->z_buffer = NULL;
	}
}

void	cleanup_map(t_data *data)
{
	if (data->map_path)
	{
		free(data->map_path);
		data->map_path = NULL;
	}
	if (data->map)
	{
		ft_free_array(data->map);
		data->map = NULL;
	}
}

static void	destroy_frame_images(t_data *data, t_animated_texture *anim)
{
	int	i;

	if (!anim->frames)
		return ;
	i = 0;
	while (i < anim->frame_count)
	{
		if (anim->frames[i].img)
			mlx_destroy_image(data->mlx, anim->frames[i].img);
		i++;
	}
	free(anim->frames);
	anim->frames = NULL;
}

void	cleanup_wall_animations(t_data *data)
{
	int	i;

	if (!data->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		destroy_frame_images(data, &data->animated_textures[i]);
		i++;
	}
	destroy_frame_images(data, &data->animated_door_texture);
	destroy_frame_images(data, &data->animated_lamp_texture);
}
