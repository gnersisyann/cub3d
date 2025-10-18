/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:59:02 by ganersis         ###   ########.fr       */
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

void	update_texture_animations(t_data *data, double delta_time)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (data->animated_textures[i].frame_count > 1)
		{
			data->animated_textures[i].animation_timer += delta_time;
			if (data->animated_textures[i].animation_timer
				>= data->animated_textures[i].animation_speed)
			{
				data->animated_textures[i].current_frame++;
				if (data->animated_textures[i].current_frame
					>= data->animated_textures[i].frame_count)
					data->animated_textures[i].current_frame = 0;
				data->animated_textures[i].animation_timer = 0.0;
			}
		}
	}
}

t_texture	*get_current_texture_frame(t_data *data, int texture_num)
{
	t_animated_texture	*anim_tex;

	if (texture_num < 0 || texture_num > 5)
		return (NULL);
	anim_tex = &data->animated_textures[texture_num];
	if (anim_tex->frame_count == 0)
		return (NULL);
	return (&anim_tex->frames[anim_tex->current_frame]);
}

int	load_door_textures(t_data *data)
{
    // Загружаем текстуры закрытых дверей (индекс 4)
    if (data->door_closed_texture_count > 0)
    {
        if (!load_animated_texture(data, &data->animated_textures[4],
                data->door_closed_textures, data->door_closed_texture_count))
        {
            printf("Error: Failed to load door closed textures\n");
            return (0);
        }
    }
    else
    {
        // Если текстуры дверей не заданы, создаем пустую анимированную текстуру
        data->animated_textures[4].frames = NULL;
        data->animated_textures[4].frame_count = 0;
        data->animated_textures[4].current_frame = 0;
        data->animated_textures[4].animation_speed = 0.1;
        data->animated_textures[4].animation_timer = 0.0;
    }
    
    // Загружаем текстуры открытых дверей (индекс 5)
    if (data->door_open_texture_count > 0)
    {
        if (!load_animated_texture(data, &data->animated_textures[5],
                data->door_open_textures, data->door_open_texture_count))
        {
            printf("Error: Failed to load door open textures\n");
            return (0);
        }
    }
    else
    {
        // Если текстуры дверей не заданы, создаем пустую анимированную текстуру
        data->animated_textures[5].frames = NULL;
        data->animated_textures[5].frame_count = 0;
        data->animated_textures[5].current_frame = 0;
        data->animated_textures[5].animation_speed = 0.1;
        data->animated_textures[5].animation_timer = 0.0;
    }
    return (1);
}

int	load_textures(t_data *data)
{
	if (!load_animated_texture(data, &data->animated_textures[0],
			data->north_textures, data->north_texture_count))
	{
		printf("Error: Failed to load north textures\n");
		return (0);
	}
	if (!load_animated_texture(data, &data->animated_textures[1],
			data->south_textures, data->south_texture_count))
	{
		printf("Error: Failed to load south textures\n");
		return (0);
	}
	if (!load_animated_texture(data, &data->animated_textures[2],
			data->west_textures, data->west_texture_count))
	{
		printf("Error: Failed to load west textures\n");
		return (0);
	}
	if (!load_animated_texture(data, &data->animated_textures[3],
			data->east_textures, data->east_texture_count))
	{
		printf("Error: Failed to load east textures\n");
		return (0);
	}
	if (!load_door_textures(data))
        return (0);
	return (1);
}
