#include "error.h"
#include "libft.h"

void	ft_error_exit(char *message, int exit_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}