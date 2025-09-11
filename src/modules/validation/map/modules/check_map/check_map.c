#include "error.h"
#include "libft.h"
#include "validation.h"

static int	is_player_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	find_player_position(char **map_lines, int *player_count,
		int *player_x, int *player_y)
{
	int	i;
	int	j;

	*player_count = 0;
	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (is_player_character(map_lines[i][j]))
			{
				(*player_count)++;
				*player_x = j;
				*player_y = i;
			}
			j++;
		}
		i++;
	}
}

static void	validate_player_count(char **map_lines)
{
	int	player_count;
	int	player_x;
	int	player_y;

	find_player_position(map_lines, &player_count, &player_x, &player_y);
	if (player_count == 0)
		ft_error_exit("No player found in map", EXIT_FAILURE);
	if (player_count > 1)
		ft_error_exit("Multiple players found in map", EXIT_FAILURE);
}

static int	get_map_width(char **map_lines)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (map_lines[i])
	{
		current_width = ft_strlen(map_lines[i]);
		if (map_lines[i][current_width - 1] == '\n')
			current_width--;
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

static int	get_map_height(char **map_lines)
{
	int	height;

	height = 0;
	while (map_lines[height])
		height++;
	return (height);
}

static char	get_map_char_safe(char **map_lines, int x, int y, int map_height)
{
	int	line_len;

	if (y < 0 || y >= map_height || x < 0)
		return ('1');
	line_len = ft_strlen(map_lines[y]);
	if (map_lines[y][line_len - 1] == '\n')
		line_len--;
	if (x >= line_len)
		return ('1');
	return (map_lines[y][x]);
}

static void	flood_fill_check(char **map_lines, int x, int y, int map_width,
		int map_height, int **visited)
{
	char	current;

	if (x < 0 || y < 0 || x >= map_width || y >= map_height)
		ft_error_exit("Player can escape from map boundaries", EXIT_FAILURE);
	if (visited[y][x])
		return ;
	current = get_map_char_safe(map_lines, x, y, map_width);
	if (current == '1')
		return ;
	if (current != '0' && !is_player_character(current))
		return ;
	visited[y][x] = 1;
	if (x == 0 || y == 0 || x >= map_width - 1 || y >= map_height - 1)
	{
		if (current == '0' || is_player_character(current))
			ft_error_exit("Map is not closed by walls", EXIT_FAILURE);
	}
	flood_fill_check(map_lines, x + 1, y, map_width, map_height, visited);
	flood_fill_check(map_lines, x - 1, y, map_width, map_height, visited);
	flood_fill_check(map_lines, x, y + 1, map_width, map_height, visited);
	flood_fill_check(map_lines, x, y - 1, map_width, map_height, visited);
}

static void	validate_map_closure(char **map_lines)
{
	int	map_width;
	int	map_height;
	int	player_count;
	int	player_x;
	int	player_y;
	int	**visited;
	int	i;

	map_width = get_map_width(map_lines);
	map_height = get_map_height(map_lines);
	find_player_position(map_lines, &player_count, &player_x, &player_y);
	visited = (int **)malloc(sizeof(int *) * map_height);
	if (!visited)
		ft_error_exit("Memory allocation failed", EXIT_FAILURE);
	i = 0;
	while (i < map_height)
	{
		visited[i] = (int *)ft_calloc(map_width, sizeof(int));
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			ft_error_exit("Memory allocation failed", EXIT_FAILURE);
		}
		i++;
	}
	flood_fill_check(map_lines, player_x, player_y, map_width, map_height,
		visited);
	i = 0;
	while (i < map_height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static void	validate_map_characters(char **map_lines)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			c = map_lines[i][j];
			if (c != '0' && c != '1' && !is_player_character(c) && c != '\n')
			{
				ft_error_exit("Invalid character in map", EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

static void	validate_map_size(char **map_lines)
{
	int	height;
	int	width;

	height = get_map_height(map_lines);
	width = get_map_width(map_lines);
	if (height < 3 || width < 3)
		ft_error_exit("Map is too small", EXIT_FAILURE);
}

void	ft_validate_map_structure(t_file_content *content, t_data *data)
{
	if (!content || !content->map_lines)
		ft_error_exit("No map data to validate", EXIT_FAILURE);
	validate_map_size(content->map_lines);
	validate_map_characters(content->map_lines);
	validate_player_count(content->map_lines);
	validate_map_closure(content->map_lines);
	int player_count, player_x, player_y;
	find_player_position(content->map_lines, &player_count, &player_x,
		&player_y);
	data->player_x = player_x;
	data->player_y = player_y;
	data->player_direction = get_map_char_safe(content->map_lines, player_x,
			player_y, get_map_width(content->map_lines));
}
