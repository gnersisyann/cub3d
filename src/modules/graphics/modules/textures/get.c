/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:52:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/01 16:48:31 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_texture	*get_current_texture_frame(t_data *data, int texture_num)
{
	t_animated_texture	*anim_tex;

	if (texture_num == 4)
	{
		if (data->animated_door_texture.frame_count == 0)
			return (NULL);
		anim_tex = &data->animated_door_texture;
		return (&anim_tex->frames[anim_tex->current_frame]);
	}
	if (texture_num < 0 || texture_num > 3)
		return (NULL);
	anim_tex = &data->animated_textures[texture_num];
	if (anim_tex->frame_count == 0)
		return (NULL);
	return (&anim_tex->frames[anim_tex->current_frame]);
}
