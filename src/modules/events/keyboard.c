/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:57 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:06:53 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "events.h"
#include "graphics.h"

int	ft_key_hook(int keycode, t_data *data)
{
    if (keycode == ESC)
        ft_exit(data);
    else if (keycode == W)
        move_forward(data);
    else if (keycode == S)
        move_backward(data);
    else if (keycode == A)
        move_left(data);
    else if (keycode == D)
        move_right(data);
    else if (keycode == LARROW)
        rotate_left(data);
    else if (keycode == RARROW)
        rotate_right(data);
    
    ft_render_next_frame(data);
    return (0);
}
