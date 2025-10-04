/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:52:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/04 16:52:58 by ganersis         ###   ########.fr       */
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
