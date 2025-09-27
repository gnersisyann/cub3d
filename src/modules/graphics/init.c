/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:12 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:18:47 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "error.h"
#include "graphics.h"
#include <stdlib.h>

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
    
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (!data->img)
        ft_error_exit("Image creation failed", EXIT_FAILURE);
    
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
                                    &data->line_length, &data->endian);
    if (!data->addr)
        ft_error_exit("Failed to get image address", EXIT_FAILURE);
    
    init_player_position(data);
}
