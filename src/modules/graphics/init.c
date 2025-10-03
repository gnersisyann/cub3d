/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:12 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:12:13 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "error.h"
#include "graphics.h"
#include "events.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	return (1);
}

int	ft_create_window(t_data *data, int width, int height, char *title)
{
	data->win = mlx_new_window(data->mlx, width, height, title);
	if (!data->win)
		return (0);
	return (1);
}

void	ft_init_graphics(t_data *data)
{
	if (!ft_init_mlx(data))
		ft_error_exit("MLX initialization failed", EXIT_FAILURE);
	if (!ft_create_window(data, WIDTH, HEIGHT, "cub3D"))
		ft_error_exit("Window creation failed", EXIT_FAILURE);
	if (!ft_load_textures(data))
		ft_error_exit("Texture loading failed", EXIT_FAILURE);

	// Set up event hooks once
	mlx_hook(data->win, 17, 1L << 2, ft_exit, data);
	mlx_hook(data->win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release, data);
}

int	ft_load_textures(t_data *data)
{
	// Load North texture
	data->north_img = mlx_xpm_file_to_image(data->mlx, data->north_texture,
		&data->tex_width, &data->tex_height);
	if (!data->north_img)
		return (0);
	data->north_data = mlx_get_data_addr(data->north_img, &data->tex_bpp,
		&data->tex_line_len, &data->tex_endian);

	// Load South texture
	data->south_img = mlx_xpm_file_to_image(data->mlx, data->south_texture,
		&data->tex_width, &data->tex_height);
	if (!data->south_img)
		return (0);
	data->south_data = mlx_get_data_addr(data->south_img, &data->tex_bpp,
		&data->tex_line_len, &data->tex_endian);

	// Load West texture
	data->west_img = mlx_xpm_file_to_image(data->mlx, data->west_texture,
		&data->tex_width, &data->tex_height);
	if (!data->west_img)
		return (0);
	data->west_data = mlx_get_data_addr(data->west_img, &data->tex_bpp,
		&data->tex_line_len, &data->tex_endian);

	// Load East texture
	data->east_img = mlx_xpm_file_to_image(data->mlx, data->east_texture,
		&data->tex_width, &data->tex_height);
	if (!data->east_img)
		return (0);
	data->east_data = mlx_get_data_addr(data->east_img, &data->tex_bpp,
		&data->tex_line_len, &data->tex_endian);

	return (1);
}
