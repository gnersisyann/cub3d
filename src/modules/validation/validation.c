/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:22:01 by letto             #+#    #+#             */
/*   Updated: 2025/11/17 00:46:53 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_validate(int argc, char **argv, t_data *data,
		t_file_content *content)
{
	ft_validate_arguments(argc, argv);
	ft_validate_map(argv[1], data, content);
}
