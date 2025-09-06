#include "error.h"
#include "libft.h"
#include "validation.h"
#include <fcntl.h>
#include <string.h>

void	ft_check_file_extension(char *filename, char *extension)
{
	size_t	filename_length;
	size_t	extension_length;

	filename_length = ft_strlen(filename);
	extension_length = ft_strlen(extension);
	if (!filename || (filename_length <= extension_length) || ft_strcmp(filename
			+ filename_length - extension_length, extension) != 0)
		ft_error_exit("Invalid file extension. Expected [something].cub",
			EXIT_FAILURE);
}

void	ft_check_file_exists(char *filename)
{
	int	fd;

	if (!filename)
		ft_error_exit("Map file does not exist", EXIT_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error_exit("Map file does not exist", EXIT_FAILURE);
	close(fd);
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
		ft_error_exit("Usage: ./cub3D <map.cub>", EXIT_FAILURE);
}