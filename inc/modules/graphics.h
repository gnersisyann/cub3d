/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:10:57 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:14:17 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"
# include <mlx.h>

int		ft_init_mlx(t_data *data);
int		ft_create_window(t_data *data, int width, int height, char *title);
void	ft_init_graphics(t_data *data);
int		ft_render_next_frame(t_data *data);

// player
void	init_player_direction(t_data *data);
void	init_player_position(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

// raycast
void	perform_dda(t_ray *ray, t_data *data);
void	calculate_wall_distance(t_ray *ray, t_data *data);
void	init_ray(t_ray *ray, t_data *data, double ray_dir_x, double ray_dir_y);
void	calculate_step_and_side_dist(t_ray *ray, t_data *data);
void	cast_rays(t_data *data);
void	cast_single_ray(t_data *data, int x, double ray_dir_x, double ray_dir_y);
void	draw_wall_stripe(t_data *data, t_ray *ray, int x);

//      utils
void	put_pixel(t_data *data, int x, int y, int color);
void	clear_screen(t_data *data);
void	draw_ceiling_and_floor(t_data *data);

#endif