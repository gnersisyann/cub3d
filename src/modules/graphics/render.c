/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:07 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 17:30:24 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_render_next_frame(t_data *data)
{
	update_texture_animations(data, 0.016);
	clear_screen(data);
	cast_rays(data);
	render_sprites(data);
	draw_minimap(data);
	draw_miniview(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
