#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>

void	ft_validate_args(int argc, char **argv)
{
	ft_check_argc(argc);
	ft_check_file_extension(argv[1], ".cub");
	ft_check_file_exists(argv[1]);
}

void	ft_validate_map(char *map_path, t_data *data)
{
	// TODO: add validation
}
