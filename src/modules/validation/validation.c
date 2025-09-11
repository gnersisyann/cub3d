#include "validation.h"

void	ft_validate(int argc, char **argv, t_data *data,
		t_file_content *content)
{
	ft_validate_arguments(argc, argv);
	ft_validate_map(argv[1], data, content);
}