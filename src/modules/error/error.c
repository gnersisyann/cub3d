#include "error.h"

void	ft_error_exit(const char *message, int exit_code)
{
	printf("Error\n%s\n", message);
	exit(exit_code);
}