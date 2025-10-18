/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:10:57 by letto             #+#    #+#             */
/*   Updated: 2025/10/04 17:52:52 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "../structs.h"

// Render functions
int			ft_render_next_frame(t_data *data);

// Init functions
int			ft_init_mlx(t_data *data);
int			ft_create_window(t_data *data, int width, int height, char *title);
void		ft_init_graphics(t_data *data);
void		setup_hooks(t_data *data);

// Game loop
int			ft_game_loop(t_data *data);
void		handle_movement(t_data *data);

// Key handling
int			ft_key_press(int keycode, t_data *data);
int			ft_key_release(int keycode, t_data *data);

// Player functions
void		init_player_position(t_data *data);
void		init_player_direction(t_data *data);
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);
void		rotate_left(t_data *data);
void		rotate_right(t_data *data);
int			mouse_move(int x, int y, t_data *data);
void		toggle_mouse_capture(t_data *data);
void		init_mouse(t_data *data);

// Raycast functions
void		cast_rays(t_data *data);
void		cast_single_ray(t_data *data, int x, double ray_dir_x,
				double ray_dir_y);
void		init_ray(t_ray *ray, t_data *data, double ray_dir_x,
				double ray_dir_y);
void		calculate_step_and_side_dist(t_ray *ray, t_data *data);
void		perform_dda(t_data *data, t_ray *ray);
void		calculate_wall_distance(t_ray *ray, t_data *data);

// Textures
int			load_textures(t_data *data);
int			load_animated_texture(t_data *data, t_animated_texture *anim_tex,
				char **texture_paths, int texture_count);
void		update_texture_animations(t_data *data, double delta_time);
t_texture	*get_current_texture_frame(t_data *data, int texture_num);
int			get_texture_pixel(t_texture *texture, int x, int y);
void		calculate_texture_coords(t_data *data, t_ray *ray, int *tex_x,
				double *step);
void		draw_texture_column(t_data *data, t_ray *ray, int x, int tex_x);

// Render
void		render_wall_column(t_data *data, t_ray *ray, int x);
void		render_textured_wall(t_data *data, t_ray *ray, int x);
void		render_floor_ceiling(t_data *data, int x, int draw_end);
void		determine_texture(t_ray *ray);

// Minimap
void		init_minimap(t_data *data);
void		draw_minimap(t_data *data);
void		draw_miniview(t_data *data);
int			get_minimap_color(t_data *data, int map_x, int map_y);
void		init_raw_data(t_pixel *px, t_data *data);
void		put_pixel_with_struct(t_pixel *px);
void		put_pixel_raw(t_pixel *px);
void		draw_player_marker(t_data *data, int dst_off_x, int dst_off_y);
void		process_miniview_pixel(t_data *data, t_coords *coords);
int			check_miniview_bounds(t_data *data, t_coords *coords);
void		draw_tile_pixels(t_data *data, int x, int y, int color);
void		draw_player_dot(t_data *data, int px, int py);

// Utils
void		clear_screen(t_data *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
