/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:43:48 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:43:48 by ganersis         ###   ########.fr       */
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
