/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:20:45 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 18:12:02 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_file_content(t_file_content *content)
{
	if (!content)
		return ;
	if (content->config_lines)
		ft_free_array(content->config_lines);
	if (content->map_lines)
		ft_free_array(content->map_lines);
	content->config_lines = NULL;
	content->map_lines = NULL;
}

static void	cleanup_sprites(t_data *data)
{
	if (data->sprites)
	{
		free(data->sprites);
		data->sprites = NULL;
		data->sprite_count = 0;
	}
}

static void	cleanup_animated_textures(t_data *data)
{
	int	i;
	int	j;

	if (!data->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (data->animated_textures[i].frames)
		{
			j = 0;
			while (j < data->animated_textures[i].frame_count)
			{
				if (data->animated_textures[i].frames[j].img)
					mlx_destroy_image(data->mlx,
						data->animated_textures[i].frames[j].img);
				j++;
			}
			free(data->animated_textures[i].frames);
			data->animated_textures[i].frames = NULL;
		}
		i++;
	}
	if (data->animated_door_texture.frames)
	{
		i = 0;
		while (i < data->animated_door_texture.frame_count)
		{
			if (data->animated_door_texture.frames[i].img)
				mlx_destroy_image(data->mlx,
					data->animated_door_texture.frames[i].img);
			i++;
		}
		free(data->animated_door_texture.frames);
		data->animated_door_texture.frames = NULL;
	}
}

void	ft_cleanup_data(t_data *data)
{
	if (!data)
		return ;
	cleanup_texture_arrays(data);
	cleanup_sprites(data);
	if (data->z_buffer)
	{
		free(data->z_buffer);
		data->z_buffer = NULL;
	}
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
	if (data->mlx)
	{
		cleanup_animated_textures(data);
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->minimap.img)
			mlx_destroy_image(data->mlx, data->minimap.img);
		if (data->minimap.view_img)
			mlx_destroy_image(data->mlx, data->minimap.view_img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	set_null(data);
}

static void	check_partial(char **curr)
{
	if (*curr)
	{
		free(*curr);
		*curr = NULL;
	}
}

void	ft_cleanup_data_partial(t_data *data)
{
	if (!data)
		return ;
	cleanup_texture_arrays(data);
	cleanup_sprites(data);
	check_partial(&data->map_path);
	if (data->map)
	{
		ft_free_array(data->map);
		data->map = NULL;
	}
}
