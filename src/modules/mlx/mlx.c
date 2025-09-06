#include "error.h"
#include "mlx.h"
#include "mlx_cub.h"
#include <stdlib.h>

void	ft_mlx_loop(void *mlx)
{
	mlx_loop(mlx);
	ft_error_exit("Loop fail", EXIT_FAILURE);
}
