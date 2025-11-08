/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 17:25:13 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_single_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (0);
	return (1);
}

int	load_animated_texture(t_data *data, t_animated_texture *anim_tex,
		char **texture_paths, int texture_count)
{
	int	i;

	if (texture_count == 0)
		return (0);
	anim_tex->frames = malloc(sizeof(t_texture) * texture_count);
	if (!anim_tex->frames)
		return (0);
	anim_tex->frame_count = texture_count;
	anim_tex->current_frame = 0;
	anim_tex->animation_speed = 0.1;
	anim_tex->animation_timer = 0.0;
	i = -1;
	while (++i < texture_count)
	{
		if (!load_single_texture(data, &anim_tex->frames[i], texture_paths[i]))
		{
			printf("Error: Failed to load texture: %s\n", texture_paths[i]);
			return (0);
		}
	}
	return (1);
}

void	update_door_animation(t_data *data, double delta_time)
{
	if (data->animated_door_texture.frame_count > 1)
	{
		data->animated_door_texture.animation_timer += delta_time;
		if (data->animated_door_texture.animation_timer >= \
data->animated_door_texture.animation_speed)
		{
			data->animated_door_texture.current_frame++;
			if (data->animated_door_texture.current_frame >= \
data->animated_door_texture.frame_count)
				data->animated_door_texture.current_frame = 0;
			data->animated_door_texture.animation_timer = 0.0;
		}
	}
}

void	update_lamp_animation(t_data *data, double delta_time)
{
    data->animated_lamp_texture.animation_timer += delta_time;
    if (data->animated_lamp_texture.animation_timer
        >= data->animated_lamp_texture.animation_speed)
    {
        data->animated_lamp_texture.animation_timer = 0.0;
        data->animated_lamp_texture.current_frame++;
        if (data->animated_lamp_texture.current_frame
            >= data->animated_lamp_texture.frame_count)
            data->animated_lamp_texture.current_frame = 0;
    }
}

void	update_texture_animations(t_data *data, double delta_time)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->animated_textures[i].frame_count > 1)
		{
			data->animated_textures[i].animation_timer += delta_time;
			if (data->animated_textures[i].animation_timer >= \
data->animated_textures[i].animation_speed)
			{
				data->animated_textures[i].current_frame++;
				if (data->animated_textures[i].current_frame >= \
data->animated_textures[i].frame_count)
					data->animated_textures[i].current_frame = 0;
				data->animated_textures[i].animation_timer = 0.0;
			}
		}
	}
	update_door_animation(data, delta_time);
	update_lamp_animation(data, delta_time);
}

int	load_textures(t_data *data)
{
	if (!load_animated_texture(data, &data->animated_textures[0],
			data->north_textures, data->north_texture_count))
		return (printf("Error: Failed to load north textures\n"), 0);
	if (!load_animated_texture(data, &data->animated_textures[1],
			data->south_textures, data->south_texture_count))
		return (printf("Error: Failed to load south textures\n"), 0);
	if (!load_animated_texture(data, &data->animated_textures[2],
			data->west_textures, data->west_texture_count))
		return (printf("Error: Failed to load west textures\n"), 0);
	if (!load_animated_texture(data, &data->animated_textures[3],
			data->east_textures, data->east_texture_count))
		return (printf("Error: Failed to load east textures\n"), 0);
	if (data->door_textures && data->door_texture_count > 0)
	{
		if (!load_animated_texture(data, &data->animated_door_texture,
				data->door_textures, data->door_texture_count))
		{
			printf("Error: Failed to load door textures\n");
			return (0);
		}
	}
	if (data->lamp_textures && data->lamp_texture_count > 0)
    {
        if (!load_animated_texture(data, &data->animated_lamp_texture,
                data->lamp_textures, data->lamp_texture_count))
        {
            printf("Error: Failed to load lamp textures\n");
            return (0);
        }
    }
	return (1);
}
