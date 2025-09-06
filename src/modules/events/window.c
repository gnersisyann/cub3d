#include "events.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_exit(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    free(data->mlx);
    printf("WINDOW CLOSED\n");
    exit(EXIT_SUCCESS);
}