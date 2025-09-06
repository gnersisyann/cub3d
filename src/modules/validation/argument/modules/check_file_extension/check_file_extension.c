#include "error.h"
#include "libft.h"
#include "validation.h"
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