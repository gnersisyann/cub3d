/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:00:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/11/08 17:21:21 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lamps(char **map_lines)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (map_lines[i][j] == 'L')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static t_sprite	*allocate_sprites(int count, t_data *data,
		t_file_content *content)
{
	t_sprite	*sprites;

	if (count == 0)
		return (NULL);
	sprites = malloc(sizeof(t_sprite) * count);
	if (!sprites)
		ft_error_exit_with_cleanup("Failed to allocate sprites", EXIT_FAILURE,
			data, content);
	return (sprites);
}

static void	init_sprite(t_sprite *sprite, int x, int y,
		t_animated_texture *texture)
{
	sprite->x = (double)x + 0.5;
	sprite->y = (double)y + 0.5;
	sprite->distance = 0.0;
	sprite->texture = texture;
}

static void	extract_lamp_positions(char **map_lines, t_sprite *sprites,
		int *sprite_index, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map_lines[i])
	{
		j = 0;
		while (map_lines[i][j])
		{
			if (map_lines[i][j] == 'L')
			{
				init_sprite(&sprites[*sprite_index], j, i,
					&data->animated_lamp_texture);
				(*sprite_index)++;
			}
			j++;
		}
		i++;
	}
}

void	parse_sprites_from_map(t_data *data, t_file_content *content)
{
	int	lamp_count;
	int	sprite_index;

	lamp_count = count_lamps(content->map_lines);
	if (lamp_count == 0)
	{
		data->sprites = NULL;
		data->sprite_count = 0;
		return ;
	}
	data->sprites = allocate_sprites(lamp_count, data, content);
	data->sprite_count = lamp_count;
	sprite_index = 0;
	extract_lamp_positions(content->map_lines, data->sprites, &sprite_index,
		data);
}
