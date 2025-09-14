#include "libft.h"
#include "utils.h"
#include <mlx.h>
#include <stdlib.h>

void	ft_free_file_content(t_file_content *content)
{
	if (!content)
		return ;
	if (content->config_lines)
		ft_free_array(content->config_lines);
	if (content->map_lines)
		ft_free_array(content->map_lines);
	content->config_lines = NULL;
	content->map_lines = NULL;
}

void	ft_cleanup_data(t_data *data)
{
	if (!data)
		return ;
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->map_path)
		free(data->map_path);
	if (data->map)
		ft_free_array(data->map);
	if (data->img && data->mlx)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->map_path = NULL;
	data->map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
}

void	ft_cleanup_data_partial(t_data *data)
{
	if (!data)
		return ;
	if (data->north_texture)
	{
		free(data->north_texture);
		data->north_texture = NULL;
	}
	if (data->south_texture)
	{
		free(data->south_texture);
		data->south_texture = NULL;
	}
	if (data->west_texture)
	{
		free(data->west_texture);
		data->west_texture = NULL;
	}
	if (data->east_texture)
	{
		free(data->east_texture);
		data->east_texture = NULL;
	}
	if (data->map_path)
	{
		free(data->map_path);
		data->map_path = NULL;
	}
}
