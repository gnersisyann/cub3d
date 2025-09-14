/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:22:28 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:22:29 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "validation.h"
#include <stdlib.h>

void	ft_check_argc(int argc)
{
	if (argc != 2)
		ft_error_exit("Usage: ./cub3D <map.cub>", EXIT_FAILURE);
}
