/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:20:45 by letto             #+#    #+#             */
/*   Updated: 2025/11/17 01:06:23 by letto            ###   ########.fr       */
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

void	cleanup_map_data(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			data->map[i] = NULL;
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
}

void	ft_cleanup_data(t_data *data)
{
	if (!data)
		return ;
	cleanup_texture_arrays(data);
	cleanup_sprites(data);
	cleanup_buffers(data);
	cleanup_map(data);
	cleanup_map_data(data);
	cleanup_mlx_resources(data);
	set_null(data);
}

void	ft_cleanup_data_partial(t_data *data)
{
	if (!data)
		return ;
	cleanup_texture_arrays(data);
	cleanup_sprites(data);
	cleanup_map(data);
	cleanup_map_data(data);
}

void	cleanup_flood_context(t_flood_context *ctx)
{
	if (ctx->visited)
		cleanup_visited_array(ctx->visited, ctx->map_height);
	if (ctx->normalized_map)
		cleanup_normalized_map(ctx->normalized_map, ctx->map_height);
}
