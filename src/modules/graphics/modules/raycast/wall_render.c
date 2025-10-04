/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:41:36 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 17:41:36 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"

void	draw_wall_stripe(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;

	if (ray->side == 1)
		color = 0x00FF0000;
	else
		color = 0x0000FF00;
	if (ray->side == 1)
		color = color >> 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_pixel(data, x, y, color);
		y++;
	}
}
