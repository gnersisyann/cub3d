/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:03 by letto             #+#    #+#             */
/*   Updated: 2025/11/27 11:45:32 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../structs.h"

void	init_structures(t_file_content *content, t_data *data);

// Cleanup functions
void	ft_cleanup_data(t_data *data);
void	ft_cleanup_data_partial(t_data *data);
void	ft_free_file_content(t_file_content *content);

// Cleanup utils
void	cleanup_sprites(t_data *data);
void	cleanup_buffers(t_data *data);
void	cleanup_map(t_data *data);
void	cleanup_wall_animations(t_data *data);

// Cleanup MLX
void	cleanup_mlx_resources(t_data *data);

// Cleanup textures
void	cleanup_texture_arrays(t_data *data);

void	set_null(t_data *data);
#endif
