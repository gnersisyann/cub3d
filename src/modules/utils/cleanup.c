/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:20:45 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 18:41:10 by ganersis         ###   ########.fr       */
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
	cleanup_sprites(data);
	cleanup_buffers(data);
	cleanup_map(data);
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
}
