#include "libft.h"
#include "utils.h"
#include <stdlib.h>

void	ft_free_file_content(t_file_content *content)
{
	if (content->config_lines)
		ft_free_array(content->config_lines);
	if (content->map_lines)
		ft_free_array(content->map_lines);
}

void	ft_cleanup_data(t_data *data)
{
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
}
