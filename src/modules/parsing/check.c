#include "libft.h"
#include "parsing.h"
#include <fcntl.h>
#include <string.h>

int	ft_check_file_extension(char *filename, char *extension)
{
	size_t	filename_length;
	size_t	extension_length;

	filename_length = ft_strlen(filename);
	extension_length = ft_strlen(extension);
	if (!filename || (filename_length <= extension_length))
		return (0);
	if (ft_strcmp(filename + filename_length - extension_length,
			extension) != 0)
		return (0);
	return (1);
}

int	ft_check_file_exists(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
