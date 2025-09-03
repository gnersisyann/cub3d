#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

void	ft_validate_args(int argc, char **argv);
int		ft_check_file_extension(char *filename, char *extension);
int		ft_check_file_exists(char *filename);

void	ft_validate_map(char *map_path, t_data *data);

#endif