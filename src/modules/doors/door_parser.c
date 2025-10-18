/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:00 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:42:24 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

void	parse_doors_from_map(t_data *data)
{
    int	y;
    int	x;

    init_door_manager(&data->door_manager);
    data->interaction_range = 1.5f;
    data->nearest_door = NULL;
    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width && data->map[y][x])
        {
            if (data->map[y][x] == 'D')
            {
                if (!add_door(&data->door_manager, x, y))
                {
                    cleanup_door_manager(&data->door_manager);
                    ft_error_exit_with_cleanup("Failed to add door",
                        EXIT_FAILURE, data, NULL);
                }
            }
            x++;
        }
        y++;
    }
}