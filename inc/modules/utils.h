#ifndef UTILS_H
# define UTILS_H

# include "validation.h"

void	init_structures(t_file_content *content, t_data *data);

void	ft_free_file_content(t_file_content *content);
void	ft_cleanup_data(t_data *data);
void	ft_cleanup_data_partial(t_data *data);

#endif