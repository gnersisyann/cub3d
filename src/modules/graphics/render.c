/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:07 by letto             #+#    #+#             */
/*   Updated: 2025/10/04 16:49:50 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "mlx.h"

int	ft_render_next_frame(t_data *data)
{
	clear_screen(data);
	cast_rays(data);
	draw_minimap(data);
	draw_miniview(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
