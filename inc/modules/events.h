/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:10:55 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:28:07 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
#define EVENTS_H

#include "cub3d.h"

int ft_exit(t_data *data);

int ft_key_press(int keycode, t_data *data);
int ft_key_release(int keycode, t_data *data);
void handle_movement(t_data *data);
int ft_game_loop(t_data *data);

#endif