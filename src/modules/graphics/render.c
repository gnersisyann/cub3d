/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:07 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:16:51 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "graphics.h"

int	ft_render_next_frame(t_data *data)
{
    clear_screen(data);
    draw_ceiling_and_floor(data);
    cast_rays(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_hook(data->win, 17, 1L << 2, ft_exit, data);
    mlx_key_hook(data->win, ft_key_hook, data);
    return (0);
}
