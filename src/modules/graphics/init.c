/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:12 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:28:58 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "error.h"
#include "events.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include "mlx.h"

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
    mlx_hook(data->win, 2, 1L<<0, ft_key_press, data);    // Key press
    mlx_hook(data->win, 3, 1L<<1, ft_key_release, data);  // Key release
    mlx_hook(data->win, 17, 1L<<2, ft_exit, data);        // Window close
    mlx_loop_hook(data->mlx, ft_game_loop, data);         // Continuous loop
}

void	ft_init_graphics(t_data *data)
{
    memset(data->keys, 0, sizeof(data->keys));
    
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
    setup_hooks(data);
}