#include "error.h"
#include "validation.h"
#include <stdlib.h>

void	ft_check_argc(int argc)
{
	if (argc != 2)
		ft_error_exit("Usage: ./cub3D <map.cub>", EXIT_FAILURE);
}
