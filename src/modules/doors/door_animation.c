/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:50:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:45:41 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

void	update_door_animation(t_door *door, float delta_time)
{
    if (door->state == DOOR_OPENING)
    {
        door->animation_progress += door->animation_speed * delta_time;
        if (door->animation_progress >= 1.0f)
        {
            door->animation_progress = 1.0f;
            door->state = DOOR_OPEN;
        }
    }
    else if (door->state == DOOR_CLOSING)
    {
        door->animation_progress -= door->animation_speed * delta_time;
        if (door->animation_progress <= 0.0f)
        {
            door->animation_progress = 0.0f;
            door->state = DOOR_CLOSED;
        }
    }
}

void	update_doors(t_door_manager *manager, float delta_time)
{
    int	i;

    i = 0;
    while (i < manager->door_count)
    {
        update_door_animation(&manager->doors[i], delta_time);
        i++;
    }
}

void	interact_with_door(t_door *door)
{
    if (door->state == DOOR_CLOSED)
        door->state = DOOR_OPENING;
    else if (door->state == DOOR_OPEN)
        door->state = DOOR_CLOSING;
}

t_door	*find_nearest_door(t_data *data, float player_x, float player_y)
{
    int		i;
    float	distance;
    float	min_distance;
    t_door	*nearest;

    nearest = NULL;
    min_distance = data->interaction_range;
    i = 0;
    while (i < data->door_manager.door_count)
    {
        distance = sqrt(pow(data->door_manager.doors[i].x - player_x, 2) +
            pow(data->door_manager.doors[i].y - player_y, 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest = &data->door_manager.doors[i];
        }
        i++;
    }
    return (nearest);
}

int	can_interact_with_door(t_data *data, float player_x, float player_y)
{
    data->nearest_door = find_nearest_door(data, player_x, player_y);
    return (data->nearest_door != NULL);
}