/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:23:17 by letto             #+#    #+#             */
/*   Updated: 2025/10/18 18:43:27 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

void	ft_validate_map(char *map_path, t_data *data, t_file_content *content)
{
	parse_cub_file(map_path, content, data);
	ft_check_config(content, data);
	ft_validate_map_structure(content, data);
	parse_doors_from_map(data);
}
