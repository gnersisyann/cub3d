#ifndef PARSING_H
#define PARSING_H

#include "cub3d.h"

void ft_validate_args(int argc, char **argv);

void ft_check_file_extension(char *filename, char *extension);
void ft_check_file_exists(char *filename);
void ft_check_argc(int argc);

void ft_validate_map(char *map_path, t_data *data);

#endif