#ifndef VALIDATION_H
#define VALIDATION_H

#include "cub3d.h"

typedef struct s_file_content {
  char **config_lines;
  char **map_lines;
} t_file_content;

void ft_validate_map(char *map_path, t_data *data);

// argument
void ft_validate_arguments(int argc, char **argv);

void ft_check_file_extension(char *filename, char *extension);
void ft_check_file_exists(char *filename);
void ft_check_argc(int argc);

// parser
t_file_content *parse_cub_file(char *filename);

char **parse_file(char *filename);
t_file_content *ft_split_file_content(char **lines);

#endif