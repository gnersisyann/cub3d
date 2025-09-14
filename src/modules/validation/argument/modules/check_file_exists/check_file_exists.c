/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_exists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:22:32 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:22:35 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "validation.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_check_file_exists(char *filename)
{
	int	fd;

	if (!filename)
		ft_error_exit("Map file does not exist", EXIT_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error_exit("Map file does not exist", EXIT_FAILURE);
	close(fd);
}
