/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:07 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:12:07 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "graphics.h"
#include "defines.h"
#include <mlx.h>
#include <stdio.h>
#include <math.h>

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static unsigned int	get_texture_pixel(t_data *data, char *tex_data, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= data->tex_width || y < 0 || y >= data->tex_height)
		return (0);

	pixel = tex_data + (y * data->tex_line_len + x * (data->tex_bpp / 8));
	return (*(unsigned int*)pixel);
}

static char	*get_wall_texture_data(t_data *data, int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0) // North-South wall
	{
		if (ray_dir_x > 0)
			return (data->east_data); // Hit from west, show east texture
		else
			return (data->west_data); // Hit from east, show west texture
	}
	else // East-West wall
	{
		if (ray_dir_y > 0)
			return (data->south_data); // Hit from north, show south texture
		else
			return (data->north_data); // Hit from south, show north texture
	}
}

static void	render_simple_raycaster(t_data *data)
{
	int x, y;

	// Clear screen with ceiling color
	for (y = 0; y < HEIGHT / 2; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			my_mlx_pixel_put(data, x, y, data->ceiling_color);
		}
	}

	// Draw floor
	for (y = HEIGHT / 2; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			my_mlx_pixel_put(data, x, y, data->floor_color);
		}
	}

	// Simple raycasting for walls
	for (x = 0; x < WIDTH; x++)
	{
		// Calculate ray direction
		double camera_x = 2 * x / (double)WIDTH - 1;
		double ray_dir_x = data->dir_x + data->plane_x * camera_x;
		double ray_dir_y = data->dir_y + data->plane_y * camera_x;

		// Current position
		int map_x = (int)data->player_x;
		int map_y = (int)data->player_y;

		// Calculate delta distances
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		// Calculate step and initial side_dist
		int step_x, step_y;
		double side_dist_x, side_dist_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player_x) * delta_dist_x;
		}

		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player_y) * delta_dist_y;
		}

		// Perform DDA
		int hit = 0;
		int side; // 0 if NS wall, 1 if EW wall

		while (hit == 0)
		{
			// Jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}

			// Check if ray has hit a wall
			if (map_x >= 0 && map_x < data->map_width &&
				map_y >= 0 && map_y < data->map_height &&
				data->map[map_y][map_x] == '1')
				hit = 1;
		}

		// Calculate distance
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - data->player_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - data->player_y + (1 - step_y) / 2) / ray_dir_y;

		// Calculate height of line to draw on screen
		int line_height = (int)(HEIGHT / perp_wall_dist);

		// Calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		// Calculate texture coordinates
		double wall_x; // where exactly the wall was hit
		if (side == 0)
			wall_x = data->player_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = data->player_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		// x coordinate on the texture
		int tex_x = (int)(wall_x * (double)data->tex_width);
		if (side == 0 && ray_dir_x > 0)
			tex_x = data->tex_width - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = data->tex_width - tex_x - 1;

		// Get appropriate texture
		char *tex_data = get_wall_texture_data(data, side, ray_dir_x, ray_dir_y);

		// Draw the textured wall stripe
		for (y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)(((y - HEIGHT / 2 + line_height / 2) * data->tex_height) / line_height);
			if (tex_y >= 0 && tex_y < data->tex_height)
			{
				unsigned int color = get_texture_pixel(data, tex_data, tex_x, tex_y);

				// Make side walls darker
				if (side == 1)
					color = (color >> 1) & 0x7F7F7F; // Darken by shifting RGB values

				my_mlx_pixel_put(data, x, y, color);
			}
		}
	}
}

int	ft_render_next_frame(t_data *data)
{
	// Only render if we need to redraw
	if (!data->needs_redraw)
		return (0);

	// Create image if not exists
	if (!data->img)
	{
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		if (!data->img)
			return (-1);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	}

	// Render the scene
	render_simple_raycaster(data);

	// Put image to window
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	data->needs_redraw = 0;
	return (0);
}

int	game_loop(t_data *data)
{
	process_movement(data);
	ft_render_next_frame(data);
	return (0);
}
