#include "utils.h"
#include <mlx.h>
#include <stdlib.h>

static void	ft_init_data(t_data *data)
{
	if (!data)
		return ;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->map_fd = 0;
	data->map_path = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->player_x = 0.0;
	data->player_y = 0.0;
	data->dir_x = 0.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.0;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->player_direction = '\0';
}

static void	ft_init_file_content(t_file_content *content)
{
	if (!content)
		return ;
	content->config_lines = NULL;
	content->map_lines = NULL;
}

void	init_structures(t_file_content *content, t_data *data)
{
	ft_init_file_content(content);
	ft_init_data(data);
}
