#include "error.h"
#include "libft.h"
#include "validation.h"
#include <stdlib.h>

static int	is_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t' || c == '\n');
}

static int	is_config_identifier(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i + 1])
	{
		if ((line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
			|| (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
			|| (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
			|| (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' '))
			return (1);
	}
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (1);
	return (0);
}

static int	is_potential_map_line(char *line)
{
	int	i;
	int	has_map_content;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (is_config_identifier(line))
		return (0);
	has_map_content = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_map_character(line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			has_map_content = 1;
		}
		i++;
	}
	return (has_map_content);
}

static int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_no_config_after_map(char **lines, int map_start_index)
{
	int	i;

	i = map_start_index;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_config_identifier(lines[i]))
			return (0);
		if (!is_empty_line(lines[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	find_map_start_index(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			if (validate_no_config_after_map(lines, i))
				return (i);
			else
				return (-2);
		}
		i++;
	}
	return (-1);
}

static char	**extract_config_lines(char **lines, int map_start_index)
{
	char	**config_lines;
	int		config_count;
	int		i;
	int		j;

	config_count = 0;
	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
			config_count++;
		i++;
	}
	config_lines = (char **)malloc(sizeof(char *) * (config_count + 1));
	if (!config_lines)
		ft_error_exit("Memory allocation failed", EXIT_FAILURE);
	j = 0;
	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
		{
			config_lines[j] = ft_strdup(lines[i]);
			if (!config_lines[j])
			{
				while (j > 0)
					free(config_lines[--j]);
				free(config_lines);
				ft_error_exit("Memory allocation failed", EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	config_lines[j] = NULL;
	return (config_lines);
}

static char	**extract_map_lines(char **lines, int map_start_index)
{
	char	**map_lines;
	int		map_count;
	int		i;
	int		j;

	map_count = 0;
	i = map_start_index;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
			map_count++;
		i++;
	}
	if (map_count == 0)
		ft_error_exit("No valid map found in file", EXIT_FAILURE);
	map_lines = (char **)malloc(sizeof(char *) * (map_count + 1));
	if (!map_lines)
		ft_error_exit("Memory allocation failed", EXIT_FAILURE);
	j = 0;
	i = map_start_index;
	while (lines[i])
	{
		if (is_potential_map_line(lines[i]))
		{
			map_lines[j] = ft_strdup(lines[i]);
			if (!map_lines[j])
			{
				while (j > 0)
					free(map_lines[--j]);
				free(map_lines);
				ft_error_exit("Memory allocation failed", EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	map_lines[j] = NULL;
	return (map_lines);
}

t_file_content	*ft_split_file_content(char **lines)
{
	t_file_content	*content;
	int				map_start_index;
	int				has_config;
	int				i;

	if (!lines || !lines[0])
		ft_error_exit("Invalid input", EXIT_FAILURE);
	content = (t_file_content *)malloc(sizeof(t_file_content));
	if (!content)
		ft_error_exit("Memory allocation failed", EXIT_FAILURE);
	
	map_start_index = find_map_start_index(lines);
	if (map_start_index == -2)
	{
		free(content);
		ft_error_exit("Configuration elements found after map start",
			EXIT_FAILURE);
	}
	if (map_start_index == -1)
	{
		free(content);
		ft_error_exit("No map found in file", EXIT_FAILURE);
	}
	has_config = 0;
	i = 0;
	while (i < map_start_index)
	{
		if (is_config_identifier(lines[i]))
		{
			has_config = 1;
			break ;
		}
		i++;
	}
	if (!has_config)
	{
		free(content);
		ft_error_exit("No configuration elements found", EXIT_FAILURE);
	}
	content->config_lines = extract_config_lines(lines, map_start_index);
	content->map_lines = extract_map_lines(lines, map_start_index);
	return (content);
}
