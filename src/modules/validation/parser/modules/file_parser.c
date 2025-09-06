#include "error.h"
#include "libft.h"
#include "validation.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static size_t	file_line_count(char *filename)
{
	size_t	count;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error_exit("Cannot open file", EXIT_FAILURE);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

char	**parse_file(char *filename)
{
	int		fd;
	size_t	line_count;
	char	**result;
	size_t	i;

	line_count = file_line_count(filename);
	if (line_count == 0)
		ft_error_exit("File is empty", EXIT_FAILURE);
	result = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!result)
		ft_error_exit("Memory allocation failed", EXIT_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(result);
		ft_error_exit("Cannot open file", EXIT_FAILURE);
	}
	i = 0;
	while (i < line_count)
	{
		result[i] = get_next_line(fd);
		if (!result[i])
			break ;
		i++;
	}
	result[i] = NULL;
	close(fd);
	return (result);
}
