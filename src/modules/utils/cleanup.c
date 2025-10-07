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

#include "libft.h"
#include "utils.h"
#include <mlx.h>
#include <stdlib.h>

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

static void	cleanup_texture_arrays(t_data *data)
{
	int	i;

	if (data->north_textures)
	{
		i = 0;
		while (i < data->north_texture_count)
		{
			if (data->north_textures[i])
				free(data->north_textures[i]);
			i++;
		}
		free(data->north_textures);
		data->north_textures = NULL;
	}
	if (data->south_textures)
	{
		i = 0;
		while (i < data->south_texture_count)
		{
			if (data->south_textures[i])
				free(data->south_textures[i]);
			i++;
		}
		free(data->south_textures);
		data->south_textures = NULL;
	}
	if (data->west_textures)
	{
		i = 0;
		while (i < data->west_texture_count)
		{
			if (data->west_textures[i])
				free(data->west_textures[i]);
			i++;
		}
		free(data->west_textures);
		data->west_textures = NULL;
	}
	if (data->east_textures)
	{
		i = 0;
		while (i < data->east_texture_count)
		{
			if (data->east_textures[i])
				free(data->east_textures[i]);
			i++;
		}
		free(data->east_textures);
		data->east_textures = NULL;
	}
}

static void	set_null(t_data *data)
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
