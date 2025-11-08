/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:40:42 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
	if (data->minimap.view_img)
		mlx_destroy_image(data->mlx, data->minimap.view_img);
}

static void	destroy_window(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
}

static void	destroy_display(t_data *data)
{
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->mlx = NULL;
}

void	cleanup_mlx_resources(t_data *data)
{
	if (!data->mlx)
		return ;
	cleanup_wall_animations(data);
	destroy_images(data);
	destroy_window(data);
	destroy_display(data);
}
