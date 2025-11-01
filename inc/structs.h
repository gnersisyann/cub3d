/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:13:59 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/01 16:19:32 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file_content
{
	char	**config_lines;
	char	**map_lines;
}	t_file_content;

typedef struct s_texture_context
{
	struct s_data			*data;
	t_file_content			*content;
}	t_texture_context;

typedef struct s_continuity_context
{
	char			**lines;
	struct s_data	*data;
	t_file_content	*content;
}	t_continuity_context;

typedef struct s_extraction_context
{
	char			**lines;
	int				map_start_index;
	struct s_data	*data;
	t_file_content	*content;
}	t_extraction_context;

typedef struct s_line_fill_context
{
	char	**lines;
	char	**target_lines;
	int		start_index;
	int		count;
}	t_line_fill_context;

typedef struct s_flood_context
{
	char			**map_lines;
	int				map_width;
	int				map_height;
	int				**visited;
	struct s_data	*data;
	t_file_content	*content;
}	t_flood_context;

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

typedef struct s_animated_texture
{
	t_texture	*frames;
	int			frame_count;
	int			current_frame;
	double		animation_speed;
	double		animation_timer;
}			t_animated_texture;

typedef struct s_minimap
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		tile;
	void	*view_img;
	char	*view_addr;
	int		view_bpp;
	int		view_len;
	int		view_endian;
	int		view_w;
	int		view_h;
	int		x;
	int		y;
}			t_minimap;

typedef struct s_pixel
{
	char	*addr;
	int		len;
	int		bpp;
	int		x;
	int		y;
	int		color;
	int		angle;
}			t_pixel;

typedef struct s_norm
{
	int	start_px;
	int	start_py;
	int	dst_off_x;
	int	dst_off_y;
}			t_norm;

typedef struct s_door
{
    int		map_x;
    int		map_y;
    double	open_offset;
    int		is_opening;
    int		is_closing;
    int		is_open;
}			t_door;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					map_fd;
	char				*map_path;
	char				**north_textures;
	char				**south_textures;
	char				**west_textures;
	char				**east_textures;
	int					north_texture_count;
	int					south_texture_count;
	int					west_texture_count;
	int					east_texture_count;
	t_texture			textures[4];
	t_animated_texture	animated_textures[4];
	int					floor_color;
	int					ceiling_color;
	double				player_x;
	double				player_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	char				**map;
	int					map_width;
	int					map_height;
	char				player_direction;
	int					keys[65536];
	int					last_mouse_x;
	int					last_mouse_y;
	double				pitch;
	int					mouse_captured;
	t_minimap			minimap;
	char				**door_textures;
    int					door_texture_count;
    t_texture			door_texture;
    t_animated_texture	animated_door_texture;
    t_door				*doors;
    int					door_count;
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
}			t_ray;

typedef struct s_coords
{
	int		y;
	int		x;
	int		screen_y;
	int		screen_x;
	int		src_x;
	int		src_y;
	char	*src;
	int		color;
	t_pixel	pixel;
}	t_coords;

typedef struct s_dup_ctx
{
	char			**config_lines;
	t_data			*data;
	t_file_content	*content;
}					t_dup_ctx;

#endif
