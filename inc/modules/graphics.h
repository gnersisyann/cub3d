#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"
# include <mlx.h>

int		ft_init_mlx(t_data *data);
int		ft_create_window(t_data *data, int width, int height, char *title);
void	ft_init_graphics(t_data *data);
int		ft_render_next_frame(t_data *data);

#endif