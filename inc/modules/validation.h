/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:07 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 18:47:36 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "../structs.h"

void	ft_validate(int argc, char **argv, t_data *data,
			t_file_content *content);

void	ft_validate_map(char *map_path, t_data *data,
			t_file_content *content);

// Argument validation
void	ft_validate_arguments(int argc, char **argv);
void	ft_check_file_extension(char *filename, char *extension, int type);
void	ft_check_file_exists(char *filename);
void	ft_check_argc(int argc);

// File parsing
void	parse_cub_file(char *filename, t_file_content *content, t_data *data);
char	**parse_file(char *filename, t_data *data, t_file_content *content);
void	ft_split_file_content(char **lines, t_file_content *content,
			t_data *data);
void	validate_no_duplicates(char **config_lines, t_data *data,
			t_file_content *content);
void	validate_texture_duplicates(char **config_lines, t_data *data,
			t_file_content *content);

// Map validation
void	ft_check_config(t_file_content *content, t_data *data);
void	ft_validate_map_structure(t_file_content *content, t_data *data);
int		validate_map_continuity(char **lines, int map_start_index, t_data *data,
			t_file_content *content);

/* config_validators.c */
int		validate_texture_path(char *path);
int		validate_color_component(char *component);
int		validate_color_line(char *line);
int		validate_all_configs(t_data *data);
void	validate_door_texture_consistency(t_data *data,\
	t_file_content *content);
void	validate_lamp_texture_consistency(t_data *data, \
	t_file_content *content);


/* config_parsers.c */
void	parse_texture_line(char *line, char **texture_path, t_data *data,
			t_file_content *content);
void	parse_animated_texture_line(char *line, char ***texture_paths,
			int *texture_count, t_texture_context *ctx);
void	parse_color_line(char *line, int *color, t_data *data,
			t_file_content *content);

/* line_validators.c */
int		is_config_identifier(char *line);
int		is_potential_map_line(char *line);
int		is_empty_line(char *line);

/* content_extractors.c */
char	**extract_config_lines(t_extraction_context *ctx);
char	**extract_map_lines(t_extraction_context *ctx);

/* map_finder.c */
void	validate_all_lines(char **lines, t_data *data, t_file_content *content);
int		find_map_start_index(char **lines, t_data *data,
			t_file_content *content);
int		check_has_config(char **lines, int map_start_index);

/* map_utils.c */
int		is_player_character(char c);
void	find_player_position(char **map_lines, int *player_count, int *player_x,
			int *player_y);
int		get_map_width(char **map_lines);
int		get_map_height(char **map_lines);
int		map_has_doors(char **map_lines);
void	parse_sprites_from_map(t_data *data, t_file_content *content);
char	**extract_all_paths_from_line(char *line, int *count);

/* map_validators.c */
void	validate_player_count(char **map_lines, t_data *data,
			t_file_content *content);
void	validate_map_characters(char **map_lines, t_data *data,
			t_file_content *content);
void	validate_map_size(char **map_lines, t_data *data,
			t_file_content *content);
char	**ft_duplicate_map(char **map_lines, int height);

/* sprite_parser.c */
void		parse_sprites_from_map(t_data *data, t_file_content *content);

/* flood_fill.c */
char	get_map_char_safe(char **map_lines, int x, int y, int map_height);
void	validate_map_closure(char **map_lines, t_data *data,
			t_file_content *content);
void	flood_fill(t_flood_context *ctx, int x, int y);
void	init_flood_context(t_flood_context *ctx, char **map_lines, t_data *data,
			t_file_content *content);
int		**allocate_visited_array(int map_width, int map_height, t_data *data,
			t_file_content *content);

/* utils */
int		count_config_lines(char **lines, int map_start_index);
void	cleanup_config_lines(char **config_lines, int j);
void	fill_config_lines(t_line_fill_context *ctx,
			t_extraction_context *ext_ctx);
int		validate_no_config_after_map(char **lines, int map_start_index,
			t_data *data, t_file_content *content);
void	cleanup_map_lines(char **map_lines, int j);
void	check_boundary_conditions(t_flood_context *ctx, int x, int y);
char	*extract_path_from_line(char *line);

#endif
