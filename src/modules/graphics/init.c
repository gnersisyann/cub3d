/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:12 by letto             #+#    #+#             */
/*   Updated: 2025/10/04 17:53:01 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release, data);
	mlx_hook(data->win, 17, 1L << 2, ft_exit, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_loop_hook(data->mlx, ft_game_loop, data);
}

void	ft_init_graphics(t_data *data)
{
	ft_memset(data->keys, 0, sizeof(data->keys));
	if (!ft_init_mlx(data))
		ft_error_exit("MLX initialization failed", EXIT_FAILURE);
	if (!ft_create_window(data, WIDTH, HEIGHT, "cub3D"))
		ft_error_exit("Window creation failed", EXIT_FAILURE);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		ft_error_exit("Image creation failed", EXIT_FAILURE);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		ft_error_exit("Failed to get image address", EXIT_FAILURE);
	if (!load_textures(data))
		ft_error_exit("Failed to load textures", EXIT_FAILURE);
	init_mouse(data);
	init_player_position(data);
	init_minimap(data);
	setup_hooks(data);
}
