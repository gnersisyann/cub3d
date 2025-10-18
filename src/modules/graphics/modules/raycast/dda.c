/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:41:42 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:57:10 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

static void	handle_door_collision(t_ray *ray, t_data *data)
{
    t_door	*door;

    door = find_door_at_position(&data->door_manager, ray->map_x, ray->map_y);
    if (door)
    {
        // Дверь считается препятствием только если она не полностью открыта
        if (door->animation_progress < 0.9f)
        {
            ray->hit = 1;
            // Выбираем текстуру в зависимости от состояния двери
            if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
                ray->texture_num = 4; // Индекс текстуры закрытой двери
            else
                ray->texture_num = 5; // Индекс текстуры открытой двери
        }
        // Если дверь почти открыта (animation_progress >= 0.9f), 
        // луч проходит дальше без установки hit = 1
    }
}

void	determine_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->texture_num = 3;
		else
			ray->texture_num = 2;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->texture_num = 1;
		else
			ray->texture_num = 0;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        
        // Проверяем границы карты
        if (ray->map_x < 0 || ray->map_x >= data->map_width || 
            ray->map_y < 0 || ray->map_y >= data->map_height)
        {
            ray->hit = 1;
            ray->texture_num = 0; // Стандартная текстура стены
            break;
        }
        
        // Проверяем стены
        if (data->map[ray->map_y][ray->map_x] == '1')
        {
            ray->hit = 1;
            // Определяем номер текстуры в зависимости от стороны
            if (ray->side == 0)
            {
                if (ray->step_x > 0)
                    ray->texture_num = 2; // West texture
                else
                    ray->texture_num = 3; // East texture
            }
            else
            {
                if (ray->step_y > 0)
                    ray->texture_num = 1; // South texture
                else
                    ray->texture_num = 0; // North texture
            }
        }
        // Проверяем двери
        else if (data->map[ray->map_y][ray->map_x] == 'D')
        {
            handle_door_collision(ray, data);
        }
    }
}