#include "validation.h"

void	ft_validate_arguments(int argc, char **argv)
{
	ft_check_argc(argc);
	ft_check_file_exists(argv[1]);
	ft_check_file_extension(argv[1], ".cub");
}
