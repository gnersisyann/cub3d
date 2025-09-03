#include "cub3d.h"
#include "error.h"
#include "graphics.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
    t_data data;

    ft_validate_args(argc, argv);
    ft_validate_map(argv[1], &data);
    
    ft_init_graphics(&data);
    ft_render_next_frame(&data);

    mlx_loop(data.mlx);
    ft_error_exit("Loop fail", EXIT_FAILURE);
}