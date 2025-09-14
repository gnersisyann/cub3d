#include "error.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_error_exit(char *message, int exit_code)
{
	printf("Error\n%s\n", message);
	exit(exit_code);
}

void	ft_error_exit_with_cleanup(char *message, int exit_code, t_data *data,
		struct s_file_content *content)
{
	printf("Error\n%s\n", message);
	if (data)
		ft_cleanup_data_partial(data);
	if (content)
		ft_free_file_content((t_file_content *)content);
	exit(exit_code);
}
