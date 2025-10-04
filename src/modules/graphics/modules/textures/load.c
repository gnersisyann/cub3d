/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/04 16:53:01 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

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

int	load_textures(t_data *data)
{
	if (!load_single_texture(data, &data->textures[0], data->north_texture))
	{
		printf("Error: Failed to load north texture: %s\n",
			data->north_texture);
		return (0);
	}
	if (!load_single_texture(data, &data->textures[1], data->south_texture))
	{
		printf("Error: Failed to load south texture: %s\n",
			data->south_texture);
		return (0);
	}
	if (!load_single_texture(data, &data->textures[2], data->west_texture))
	{
		printf("Error: Failed to load west texture: %s\n", data->west_texture);
		return (0);
	}
	if (!load_single_texture(data, &data->textures[3], data->east_texture))
	{
		printf("Error: Failed to load east texture: %s\n", data->east_texture);
		return (0);
	}
	return (1);
}
