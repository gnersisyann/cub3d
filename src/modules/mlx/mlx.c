/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:12:23 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:12:24 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "mlx.h"
#include "mlx_cub.h"
#include <stdlib.h>

void	ft_mlx_loop(void *mlx)
{
	mlx_loop(mlx);
	ft_error_exit("Loop fail", EXIT_FAILURE);
}
