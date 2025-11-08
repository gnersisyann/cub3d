/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 17:29:17 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ===== START: Calculate sprite distance =====
static void	calculate_sprite_distances(t_data *data)
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
// ===== END: Calculate sprite distance =====

// ===== START: Sort sprites by distance (bubble sort) =====
static void	sort_sprites(t_sprite *sprites, int count)
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
// ===== END: Sort sprites by distance =====

// ===== START: Transform sprite to screen space =====
typedef struct s_sprite_transform
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}			t_sprite_transform;

static void	init_sprite_transform(t_data *data, t_sprite *sprite,
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
	transform->sprite_x = (int)((WIDTH / 2) * (1 + transform->transform_x
				/ transform->transform_y));
}
// ===== END: Transform sprite to screen space =====

// ===== START: Calculate sprite dimensions =====
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
	transform->draw_start_x = -transform->sprite_width / 2
		+ transform->sprite_x;
	if (transform->draw_start_x < 0)
		transform->draw_start_x = 0;
	transform->draw_end_x = transform->sprite_width / 2 + transform->sprite_x;
	if (transform->draw_end_x >= WIDTH)
		transform->draw_end_x = WIDTH - 1;
}

// ===== START: Draw sprite column =====
static void	draw_sprite_stripe(t_data *data, t_sprite_transform *transform,
		t_texture *texture, int stripe)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	d;

	tex_x = (int)(256 * (stripe - (-transform->sprite_width / 2
					+ transform->sprite_x)) * texture->width
			/ transform->sprite_width) / 256;
	if (transform->transform_y > 0 && stripe > 0 && stripe < WIDTH)
	{
		y = transform->draw_start_y;
		while (y < transform->draw_end_y)
		{
			d = (y)*256 - HEIGHT * 128 + transform->sprite_height * 128;
			tex_y = ((d * texture->height) / transform->sprite_height) / 256;
			color = get_texture_pixel(texture, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0x00FF00FF)
				my_mlx_pixel_put(data, stripe, y, color);
			y++;
		}
	}
}
// ===== END: Draw sprite column =====

// ===== START: Render single sprite =====
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
// ===== END: Render single sprite =====

// ===== START: Main sprite rendering function =====
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
// ===== END: Main sprite rendering function =====