/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:09 by letto             #+#    #+#             */
/*   Updated: 2025/10/04 16:40:18 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_texture
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
    int		width;
    int		height;
}			t_texture;

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
    t_texture	textures[4];
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
    int		keys[65536];
}			t_data;

typedef struct s_ray
{
    double	ray_dir_x;
    double	ray_dir_y;
    int		map_x;
    int		map_y;
    double	side_dist_x;
    double	side_dist_y;
    double	delta_dist_x;
    double	delta_dist_y;
    double	perp_wall_dist;
    int		step_x;
    int		step_y;
    int		hit;
    int		side;
    int		line_height;
    int		draw_start;
    int		draw_end;
	int		texture_num;
}	t_ray;

#endif