/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:26 by letto             #+#    #+#             */
/*   Updated: 2025/09/27 17:28:16 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "graphics.h"
#include "mlx_cub.h"
#include "utils.h"
#include "validation.h"

int	main(int argc, char **argv)
{
    t_data			data;
    t_file_content	content;

    init_structures(&content, &data);
    ft_validate(argc, argv, &data, &content);
    ft_init_graphics(&data);
    ft_mlx_loop(data.mlx);
    ft_cleanup_data(&data);
}
