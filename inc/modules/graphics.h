/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:10:57 by letto             #+#    #+#             */
/*   Updated: 2025/10/04 17:00:24 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"

// Render functions
int		ft_render_next_frame(t_data *data);

// Init functions  
int		ft_init_mlx(t_data *data);
int		ft_create_window(t_data *data, int width, int height, char *title);
void	ft_init_graphics(t_data *data);
void	setup_hooks(t_data *data);

// Game loop
int		ft_game_loop(t_data *data);
void	handle_movement(t_data *data);

// Key handling
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);

// Player functions
void	init_player_position(t_data *data);
void	init_player_direction(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

// Raycast functions
void	cast_rays(t_data *data);
void	cast_single_ray(t_data *data, int x, double ray_dir_x, double ray_dir_y);
void	init_ray(t_ray *ray, t_data *data, double ray_dir_x, double ray_dir_y);
void	calculate_step_and_side_dist(t_ray *ray, t_data *data);
void	perform_dda(t_data *data, t_ray *ray);
void	calculate_wall_distance(t_ray *ray, t_data *data);

// Textures
int		load_textures(t_data *data);
int		get_texture_pixel(t_texture *texture, int x, int y);
void	calculate_texture_coords(t_data *data, t_ray *ray, int *tex_x, 
            double *step);
void	draw_texture_column(t_data *data, t_ray *ray, int x, int tex_x);

// Render
void	render_wall_column(t_data *data, t_ray *ray, int x);
void	render_textured_wall(t_data *data, t_ray *ray, int x);
void	render_floor_ceiling(t_data *data, int x, int draw_end);
void	determine_texture(t_ray *ray);

// Utils
void	clear_screen(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif