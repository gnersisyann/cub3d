/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 18:51:08 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_sprite_dimensions(t_sprite_transform *transform)
{
	transform->sprite_height = abs((int)(HEIGHT / transform->transform_y));
	transform->draw_start_y = -transform->sprite_height / 2 + HEIGHT / 2;
	if (transform->draw_start_y < 0)
		transform->draw_start_y = 0;
	transform->draw_end_y = transform->sprite_height / 2 + HEIGHT / 2;
	if (transform->draw_end_y >= HEIGHT)
		transform->draw_end_y = HEIGHT - 1;
	transform->sprite_width = abs((int)(HEIGHT / transform->transform_y));
	transform->draw_start_x = -transform->sprite_width / 2.0
		+ transform->sprite_x;
	if (transform->draw_start_x < 0)
		transform->draw_start_x = 0;
	transform->draw_end_x = transform->sprite_width / 2.0 + transform->sprite_x;
	if (transform->draw_end_x >= WIDTH)
		transform->draw_end_x = WIDTH - 1;
}

static int	get_sprite_pixel(t_texture *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0xFF00FF);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static void	draw_sprite_stripe(t_data *data, t_sprite_transform *transform,
		t_texture *texture, int stripe)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	d;

	tex_x = (int)(256 * (stripe - (-transform->sprite_width / 2.0
					+ transform->sprite_x)) * texture->width
			/ transform->sprite_width) / 256;
	if (transform->transform_y > 0 && stripe >= 0 && stripe < WIDTH
		&& transform->transform_y < data->z_buffer[stripe])
	{
		y = transform->draw_start_y;
		while (y < transform->draw_end_y)
		{
			d = y * 256 - HEIGHT * 128 + transform->sprite_height * 128;
			tex_y = ((d * texture->height) / transform->sprite_height) / 256;
			color = get_sprite_pixel(texture, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0x00FF00FF)
				my_mlx_pixel_put(data, stripe, y, color);
			y++;
		}
	}
}

static void	render_sprite(t_data *data, t_sprite *sprite)
{
	t_sprite_transform	transform;
	t_texture			*texture;
	int					stripe;

	init_sprite_transform(data, sprite, &transform);
	if (transform.transform_y <= 0)
		return ;
	calculate_sprite_dimensions(&transform);
	texture = &sprite->texture->frames[sprite->texture->current_frame];
	stripe = transform.draw_start_x;
	while (stripe < transform.draw_end_x)
	{
		draw_sprite_stripe(data, &transform, texture, stripe);
		stripe++;
	}
}

void	render_sprites(t_data *data)
{
	int	i;

	if (!data->sprites || data->sprite_count == 0)
		return ;
	calculate_sprite_distances(data);
	sort_sprites(data->sprites, data->sprite_count);
	i = 0;
	while (i < data->sprite_count)
	{
		render_sprite(data, &data->sprites[i]);
		i++;
	}
}
