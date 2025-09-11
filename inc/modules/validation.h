#ifndef VALIDATION_H
# define VALIDATION_H

# include "cub3d.h"

// TODO: fix header

typedef struct s_file_content
{
	char	**config_lines;
	char	**map_lines;
}			t_file_content;

void		ft_validate(int argc, char **argv, t_data *data,
				t_file_content *content);

void		ft_validate_map(char *map_path, t_data *data,
				t_file_content *content);

// argument
void		ft_validate_arguments(int argc, char **argv);

void		ft_check_file_extension(char *filename, char *extension, int type);
void		ft_check_file_exists(char *filename);
void		ft_check_argc(int argc);

// parser
void		parse_cub_file(char *filename, t_file_content *content);

char		**parse_file(char *filename);
void		ft_split_file_content(char **lines, t_file_content *content);

void		ft_check_config(t_file_content *content, t_data *data);
void		ft_validate_map_structure(t_file_content *content, t_data *data);

#endif