#include "graphics.h"
#include "events.h"

int	ft_render_next_frame(t_data *data)
{
	mlx_hook(data->win, 17, 1L << 2, ft_exit, data);
	mlx_key_hook(data->win, ft_key_hook, data);
	return (0);
}