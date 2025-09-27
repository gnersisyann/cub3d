/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:23:17 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:23:18 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

void	ft_validate_map(char *map_path, t_data *data, t_file_content *content)
{
	parse_cub_file(map_path, content, data);
	ft_check_config(content, data);
	ft_validate_map_structure(content, data);
}
