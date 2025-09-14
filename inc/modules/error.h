#ifndef ERROR_H
# define ERROR_H

# include "cub3d.h"

struct	s_file_content;

void	ft_error_exit(char *message, int exit_code);
void	ft_error_exit_with_cleanup(char *message, int exit_code, t_data *data,
			struct s_file_content *content);

#endif