/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:54 by letto             #+#    #+#             */
/*   Updated: 2025/11/17 00:58:47 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	ft_cleanup_data(data);
	exit(EXIT_SUCCESS);
}
