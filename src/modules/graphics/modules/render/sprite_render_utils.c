/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:50:41 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:50:41 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_sprite_distances(t_data *data)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < data->sprite_count)
	{
		dx = data->sprites[i].x - data->player_x;
		dy = data->sprites[i].y - data->player_y;
		data->sprites[i].distance = (dx * dx + dy * dy);
		i++;
	}
}

void	sort_sprites(t_sprite *sprites, int count)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	init_sprite_transform(t_data *data, t_sprite *sprite,
		t_sprite_transform *transform)
{
	transform->sprite_x = sprite->x - data->player_x;
	transform->sprite_y = sprite->y - data->player_y;
	transform->inv_det = 1.0 / (data->plane_x * data->dir_y - data->dir_x
			* data->plane_y);
	transform->transform_x = transform->inv_det * (data->dir_y
			* transform->sprite_x - data->dir_x * transform->sprite_y);
	transform->transform_y = transform->inv_det * (-data->plane_y
			* transform->sprite_x + data->plane_x * transform->sprite_y);
	transform->sprite_x = (int)((WIDTH / 2.0) * (1 + transform->transform_x
				/ transform->transform_y));
}
