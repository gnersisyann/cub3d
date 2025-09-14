/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:07 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:29:15 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "cub3d.h"

typedef struct s_file_content
{
	char	**config_lines;
	char	**map_lines;
}			t_file_content;

void		ft_validate(int argc, char **argv, t_data *data,
				t_file_content *content);

void		ft_validate_map(char *map_path, t_data *data,
				t_file_content *content);

// Argument validation
void		ft_validate_arguments(int argc, char **argv);
void		ft_check_file_extension(char *filename, char *extension, int type);
void		ft_check_file_exists(char *filename);
void		ft_check_argc(int argc);

// File parsing
void		parse_cub_file(char *filename, t_file_content *content,
				t_data *data);
char		**parse_file(char *filename, t_data *data, t_file_content *content);
void		ft_split_file_content(char **lines, t_file_content *content,
				t_data *data);
// Map validation
void		ft_check_config(t_file_content *content, t_data *data);
void		ft_validate_map_structure(t_file_content *content, t_data *data);

/* config_validators.c */
int			validate_texture_path(char *path);
int			validate_color_component(char *component);
int			validate_color_line(char *line);
int			validate_all_configs(t_data *data);

/* config_parsers.c */
void		parse_texture_line(char *line, char **texture_path, t_data *data,
				t_file_content *content);
void		parse_color_line(char *line, int *color, t_data *data,
				t_file_content *content);

#endif