/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:54 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:11:55 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	printf("WINDOW CLOSED\n");
	exit(EXIT_SUCCESS);
}
