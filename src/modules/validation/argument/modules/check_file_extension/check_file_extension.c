/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:22:46 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:22:46 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "validation.h"
#include <string.h>

void	ft_check_file_extension(char *filename, char *extension, int type)
{
	size_t	filename_length;
	size_t	extension_length;

	filename_length = ft_strlen(filename);
	extension_length = ft_strlen(extension);
	if (!filename || (filename_length <= extension_length) || ft_strcmp(filename
			+ filename_length - extension_length, extension) != 0)
	{
		if (type)
			ft_error_exit("Invalid file extension. Expected [something].cub",
				EXIT_FAILURE);
		else
			ft_error_exit("Invalid texture extension. Expected [something].xpm",
				EXIT_FAILURE);
	}
}
