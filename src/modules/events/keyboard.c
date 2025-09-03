#include "events.h"

int	ft_key_hook(int keycode, t_data *data)
{
    if (keycode == ESC)
        ft_exit(data);
    return (0);
}