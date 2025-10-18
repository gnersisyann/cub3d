/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:07 by letto             #+#    #+#             */
/*   Updated: 2025/10/18 18:55:44 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

static int	get_wall_height_for_door(t_ray *ray, t_data *data)
{
    t_door	*door;
    float	height_multiplier;

    door = find_door_at_position(&data->door_manager, ray->map_x, ray->map_y);
    if (door)
    {
        // Высота двери зависит от прогресса анимации
        // animation_progress: 0.0 = полностью закрыта, 1.0 = полностью открыта
        height_multiplier = 1.0f - door->animation_progress;
        if (height_multiplier < 0.1f)
            height_multiplier = 0.1f; // Минимальная высота для видимости
        return ((int)(ray->line_height * height_multiplier));
    }
    return (ray->line_height);
}

static void	calculate_draw_limits_for_door(t_ray *ray, t_data *data)
{
    int	adjusted_height;


    if (ray->texture_num == 4 || ray->texture_num == 5) // Текстуры дверей
    {
        adjusted_height = get_wall_height_for_door(ray, data);
        
        // Пересчитываем границы рисования для двери
        ray->draw_start = HEIGHT / 2 - adjusted_height / 2;
        ray->draw_end = HEIGHT / 2 + adjusted_height / 2;
        
        if (ray->draw_start < 0)
            ray->draw_start = 0;
        if (ray->draw_end >= HEIGHT)
            ray->draw_end = HEIGHT - 1;
    }
}

void	draw_textured_line(t_data *data, t_ray *ray, int x)
{
    t_texture	*texture;
    double		wall_x;
    int			tex_x;
    int			y;
    int			tex_y;
    int			color;
    double		step;
    double		tex_pos;

    // Получаем текущий кадр анимированной текстуры
    texture = get_current_texture_frame(data, ray->texture_num);
    if (!texture)
        return;

    // Вычисляем координату x на стене
    if (ray->side == 0)
        wall_x = data->player_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = data->player_x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);

    // Вычисляем x координату текстуры
    tex_x = (int)(wall_x * (double)texture->width);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        tex_x = texture->width - tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        tex_x = texture->width - tex_x - 1;

    // Корректируем границы рисования для дверей
    calculate_draw_limits_for_door(ray, data);

    // Вычисляем шаг и начальную позицию текстуры
    step = 1.0 * texture->height / ray->line_height;
    tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;

    // Рисуем текстуру
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        color = *(int *)(texture->addr + (tex_y * texture->line_length + 
            tex_x * (texture->bits_per_pixel / 8)));
        
        // Затемняем боковые стены
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
            
        mlx_pixel_put(data->mlx,data->win, x, y, color);
        y++;
    }
}

int	ft_render_next_frame(t_data *data)
{
	update_texture_animations(data, 0.016);
    update_doors(&data->door_manager, 0.016);
    can_interact_with_door(data, data->player_x, data->player_y);
	clear_screen(data);
	cast_rays(data);
	draw_minimap(data);
	draw_miniview(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
