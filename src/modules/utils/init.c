/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:21:45 by letto             #+#    #+#             */
/*   Updated: 2025/11/01 16:33:54 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_null(t_data *data)
{
	data->map_path = NULL;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->north_textures = NULL;
	data->south_textures = NULL;
	data->west_textures = NULL;
	data->east_textures = NULL;
	data->north_texture_count = 0;
	data->south_texture_count = 0;
	data->west_texture_count = 0;
	data->east_texture_count = 0;
}

static void	ft_init_data_helper(t_data *data)
{
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->player_x = 0.0;
	data->player_y = 0.0;
	data->dir_x = 0.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.0;
	data->door_textures = NULL;
    data->door_texture_count = 0;
    data->doors = NULL;
    data->door_count = 0;
}

static void	ft_init_data(t_data *data)
{
	if (!data)
		return ;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->map_fd = 0;
	data->map_path = NULL;
	data->north_textures = NULL;
	data->south_textures = NULL;
	data->west_textures = NULL;
	data->east_textures = NULL;
	data->north_texture_count = 0;
	data->south_texture_count = 0;
	data->west_texture_count = 0;
	data->east_texture_count = 0;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_direction = '\0';
	ft_init_data_helper(data);
}

static void	ft_init_file_content(t_file_content *content)
{
	if (!content)
		return ;
	content->config_lines = NULL;
	content->map_lines = NULL;
}

void	init_structures(t_file_content *content, t_data *data)
{
	ft_init_file_content(content);
	ft_init_data(data);
}
