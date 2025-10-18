/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:40:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:43:43 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door_manager(t_door_manager *manager)
{
    manager->doors = NULL;
    manager->door_count = 0;
    manager->max_doors = 0;
}

void	cleanup_door_manager(t_door_manager *manager)
{
    if (manager->doors)
    {
        free(manager->doors);
        manager->doors = NULL;
    }
    manager->door_count = 0;
    manager->max_doors = 0;
}

static int	resize_door_array(t_door_manager *manager)
{
    t_door	*new_doors;
    int		new_size;
    int		i;

    new_size = manager->max_doors == 0 ? 10 : manager->max_doors * 2;
    new_doors = malloc(sizeof(t_door) * new_size);
    if (!new_doors)
        return (0);
    i = 0;
    while (i < manager->door_count)
    {
        new_doors[i] = manager->doors[i];
        i++;
    }
    if (manager->doors)
        free(manager->doors);
    manager->doors = new_doors;
    manager->max_doors = new_size;
    return (1);
}

int	add_door(t_door_manager *manager, int x, int y)
{
    t_door	*new_door;

    if (manager->door_count >= manager->max_doors)
    {
        if (!resize_door_array(manager))
            return (0);
    }
    new_door = &manager->doors[manager->door_count];
    new_door->x = x;
    new_door->y = y;
    new_door->state = DOOR_CLOSED;
    new_door->animation_progress = 0.0f;
    new_door->animation_speed = 2.0f;
    new_door->key_required = 'E';
    manager->door_count++;
    return (1);
}

t_door	*find_door_at_position(t_door_manager *manager, int x, int y)
{
    int	i;

    i = 0;
    while (i < manager->door_count)
    {
        if (manager->doors[i].x == x && manager->doors[i].y == y)
            return (&manager->doors[i]);
        i++;
    }
    return (NULL);
}