#include "graphics.h"
#include "error.h"
#include <stdio.h>

int	ft_init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
    {
        printf(" !! MLX INIT KO !!\n");
        return (0);
    }
    return (1);
}

int	ft_create_window(t_data *data, int width, int height, char *title)
{
    data->win = mlx_new_window(data->mlx, width, height, title);
    if (!data->win)
    {
        printf(" !! WINDOW CREATE KO !!\n");
        return (0);
    }
    return (1);
}

void	ft_init_graphics(t_data *data)
{
    if (!ft_init_mlx(data))
        ft_error_exit("MLX initialization failed", EXIT_FAILURE);
    if (!ft_create_window(data, WIDTH, HEIGHT, "cub3D"))
        ft_error_exit("Window creation failed", EXIT_FAILURE);
}