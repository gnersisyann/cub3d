/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:21:45 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:21:45 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <mlx.h>
#include <stdlib.h>

static void	ft_init_data_helper(t_data *data)
{
	data->floor_color = -1;  // Use -1 to indicate unset
	data->ceiling_color = -1;
	data->player_x = 0.0;
	data->player_y = 0.0;
	data->dir_x = 0.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.0;
	data->key_w = 0;
	data->key_s = 0;
	data->key_a = 0;
	data->key_d = 0;
	data->key_left = 0;
	data->key_right = 0;
	data->needs_redraw = 1;
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
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->north_img = NULL;
	data->south_img = NULL;
	data->west_img = NULL;
	data->east_img = NULL;
	data->north_data = NULL;
	data->south_data = NULL;
	data->west_data = NULL;
	data->east_data = NULL;
	data->tex_width = 0;
	data->tex_height = 0;
	data->tex_bpp = 0;
	data->tex_line_len = 0;
	data->tex_endian = 0;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->player_x = 0.0;
	data->player_y = 0.0;
	data->dir_x = 0.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.0;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_direction = '\0';
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
