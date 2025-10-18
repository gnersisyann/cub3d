/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:41:22 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:55:13 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
#define DOOR_H

#include "cub3d.h"

void	init_door_manager(t_door_manager *manager);
void	cleanup_door_manager(t_door_manager *manager);
int		add_door(t_door_manager *manager, int x, int y);
t_door	*find_door_at_position(t_door_manager *manager, int x, int y);
void	parse_doors_from_map(t_data *data);

void	update_door_animation(t_door *door, float delta_time);
void	update_doors(t_door_manager *manager, float delta_time);

void	interact_with_door(t_door *door);
t_door	*find_nearest_door(t_data *data, float player_x, float player_y);
int		can_interact_with_door(t_data *data, float player_x, float player_y);

#endif