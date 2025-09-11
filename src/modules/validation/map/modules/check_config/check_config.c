#include "error.h"
#include "libft.h"
#include "validation.h"
#include <fcntl.h>

static int	validate_texture_path(char *path)
{
	int	fd;

	if (!path)
		return (0);
	ft_check_file_extension(path, ".xpm", 0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	validate_color_component(char *component)
{
	int	value;
	int	i;

	if (!component)
		return (0);
	i = 0;
	while (component[i])
	{
		if (!ft_isdigit(component[i]))
			return (0);
		i++;
	}
	value = ft_atoi(component);
	return (value >= 0 && value <= 255);
}

static int	validate_color_line(char *line)
{
	char	**components;
	int		result;

	components = ft_split(line, ',');
	if (!components)
		return (0);
	if (!components[0] || !components[1] || !components[2] || components[3])
	{
		ft_free_array(components);
		return (0);
	}
	result = validate_color_component(components[0])
		&& validate_color_component(components[1])
		&& validate_color_component(components[2]);
	ft_free_array(components);
	return (result);
}

static void	parse_texture_line(char *line, char **texture_path)
{
	char	*path_start;

	if (*texture_path)
		ft_error_exit("Duplicate texture identifier", EXIT_FAILURE);
	path_start = line + 2;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	if (!*path_start)
		ft_error_exit("Missing texture path", EXIT_FAILURE);
	*texture_path = ft_strtrim(path_start, " \t\n");
	if (!validate_texture_path(*texture_path))
		ft_error_exit("Invalid texture path", EXIT_FAILURE);
}

static void	parse_color_line(char *line, int *color)
{
	char	*color_start;
	char	**components;

	if (*color != -1)
		ft_error_exit("Duplicate color identifier", EXIT_FAILURE);
	color_start = line + 1;
	while (*color_start && (*color_start == ' ' || *color_start == '\t'))
		color_start++;
	if (!*color_start)
		ft_error_exit("Missing color values", EXIT_FAILURE);
	color_start = ft_strtrim(color_start, " \t\n");
	if (!validate_color_line(color_start))
		ft_error_exit("Invalid color format", EXIT_FAILURE);
	components = ft_split(color_start, ',');
	*color = (ft_atoi(components[0]) << 16) | (ft_atoi(components[1]) << 8) | ft_atoi(components[2]);
	ft_free_array(components);
	free(color_start);
}

void	ft_check_config(t_file_content *content, t_data *data)
{
	int		i;
	char	*line;

	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	if (!content->config_lines)
		ft_error_exit("No configuration found", EXIT_FAILURE);
	i = 0;
	while (content->config_lines[i])
	{
		line = content->config_lines[i];
		if (!line || !line[0] || line[0] == '\n')
		{
			i++;
			continue ;
		}
		// TODO: fix case, when writing unnecessary symbols after config before map
		if (ft_strncmp(line, "NO ", 3) == 0) 
			parse_texture_line(line, &data->north_texture);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			parse_texture_line(line, &data->south_texture);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			parse_texture_line(line, &data->west_texture);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			parse_texture_line(line, &data->east_texture);
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color_line(line, &data->floor_color);
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color_line(line, &data->ceiling_color);
		else
			ft_error_exit("Unknown configuration identifier", EXIT_FAILURE);
		i++;
	}
	if (!data->north_texture || !data->south_texture || !data->west_texture
		|| !data->east_texture)
		ft_error_exit("Missing texture configuration", EXIT_FAILURE);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		ft_error_exit("Missing color configuration", EXIT_FAILURE);
}
