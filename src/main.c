#include "cub3d.h"
#include "graphics.h"
#include "mlx_cub.h"
#include "validation.h"

int	main(int argc, char **argv)
{
	t_data data;
	t_file_content content;

	ft_validate(argc, argv, &data, &content);

	ft_init_graphics(&data);
	ft_render_next_frame(&data);

	ft_mlx_loop(data.mlx);
}