/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:20:45 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:20:45 by letto            ###   ########.fr       */
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

void	ft_cleanup_data(t_data *data)
{
	if (!data)
		return ;
	cleanup_texture_arrays(data);
	if (data->map_path)
		free(data->map_path);
	if (data->map)
		ft_free_array(data->map);
	if (data->img && data->mlx)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
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
	check_partial(&data->map_path);
}
