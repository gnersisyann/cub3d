/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:26 by letto             #+#    #+#             */
/*   Updated: 2025/11/08 18:04:39 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_file_content	content;

	init_structures(&content, &data);
	ft_validate(argc, argv, &data, &content);
	ft_init_graphics(&data);
	ft_mlx_loop(data.mlx);
	ft_cleanup_data(&data);
	ft_free_file_content(&content);
}
