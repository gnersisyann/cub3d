/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:09 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:11:10 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		map_fd;
	char	*map_path;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	void	*north_img;
	void	*south_img;
	void	*west_img;
	void	*east_img;
	char	*north_data;
	char	*south_data;
	char	*west_data;
	char	*east_data;
	int		tex_width;
	int		tex_height;
	int		tex_bpp;
	int		tex_line_len;
	int		tex_endian;
	int		floor_color;
	int		ceiling_color;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	**map;
	int		map_width;
	int		map_height;
	char	player_direction;

	// Key states for continuous movement
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	int		needs_redraw;
}			t_data;

#endif
