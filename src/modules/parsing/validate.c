#include "error.h"
#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>

void	ft_validate_args(int argc, char **argv)
{
    if (argc != 2)
        ft_error_exit("Usage: ./cub3D <map.cub>", EXIT_FAILURE);
    if (!ft_check_file_extension(argv[1], ".cub"))
        ft_error_exit("Invalid file extension. Expected [something].cub",
            EXIT_FAILURE);
    if (!ft_check_file_exists(argv[1]))
        ft_error_exit("Map file does not exist", EXIT_FAILURE);
}

void	ft_validate_map(char *map_path, t_data *data)
{
    // TODO: add validation
}