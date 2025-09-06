#include "validation.h"

void	ft_validate(int argc, char **argv, t_data *data)
{
	ft_validate_arguments(argc, argv);
	ft_validate_map(argv[1], data);
}