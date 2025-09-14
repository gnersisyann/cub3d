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
static void	parse_texture_line(char *line, char **texture_path, t_data *data,
		t_file_content *content)
{
	char	*path_start;

	if (*texture_path)
		ft_error_exit_with_cleanup("Duplicate texture identifier", EXIT_FAILURE,
			data, content);
	path_start = line + 2;
	while (*path_start && (*path_start == ' ' || *path_start == '\t'))
		path_start++;
	if (!*path_start)
		ft_error_exit_with_cleanup("Missing texture path", EXIT_FAILURE, data,
			content);
	*texture_path = ft_strtrim(path_start, " \t\n");
	if (!validate_texture_path(*texture_path))
		ft_error_exit_with_cleanup("Invalid texture path", EXIT_FAILURE, data,
			content);
}


static void	parse_color_line(char *line, int *color, t_data *data,
		t_file_content *content)
{
	char	*color_start;
	char	**components;

	if (*color != -1)
		ft_error_exit_with_cleanup("Duplicate color identifier", EXIT_FAILURE,
			data, content);
	color_start = line + 1;
	while (*color_start && (*color_start == ' ' || *color_start == '\t'))
		color_start++;
	if (!*color_start)
		ft_error_exit_with_cleanup("Missing color values", EXIT_FAILURE, data,
			content);
	color_start = ft_strtrim(color_start, " \t\n");
	if (!validate_color_line(color_start))
	{
		free(color_start);
		ft_error_exit_with_cleanup("Invalid color format", EXIT_FAILURE, data,
			content);
	}
	components = ft_split(color_start, ',');
	*color = (ft_atoi(components[0]) << 16) | (ft_atoi(components[1]) << 8) | ft_atoi(components[2]);
	ft_free_array(components);
	free(color_start);
}


void	ft_check_config(t_file_content *content, t_data *data)
{
	int i;
	char *line;

	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	if (!content->config_lines)
		ft_error_exit_with_cleanup("No configuration found", EXIT_FAILURE, data,
			content);
	i = 0;
	while (content->config_lines[i])
	{
		line = content->config_lines[i];
		if (!line || !line[0] || line[0] == '\n')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(line, "NO ", 3) == 0)
			parse_texture_line(line, &data->north_texture, data, content);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			parse_texture_line(line, &data->south_texture, data, content);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			parse_texture_line(line, &data->west_texture, data, content);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			parse_texture_line(line, &data->east_texture, data, content);
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color_line(line, &data->floor_color, data, content);
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color_line(line, &data->ceiling_color, data, content);
		else
			ft_error_exit_with_cleanup("Unknown configuration identifier",
				EXIT_FAILURE, data, content);
		i++;
	}
	if (!data->north_texture || !data->south_texture || !data->west_texture
		|| !data->east_texture)
		ft_error_exit_with_cleanup("Missing texture configuration",
			EXIT_FAILURE, data, content);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		ft_error_exit_with_cleanup("Missing color configuration", EXIT_FAILURE,
			data, content);
}