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

// #include <stdio.h>
// #include <string.h>

// static void	print_file_content(t_file_content *content) // FOR_TESTING
// {
// 	int i;

// 	if (!content)
// 	{
// 		printf("❌ Content is NULL\n");
// 		return ;
// 	}
// 	printf("📋 =========================\n");
// 	printf("    FILE CONTENT ANALYSIS\n");
// 	printf("📋 =========================\n\n");
// 	printf("🔧 CONFIG LINES:\n");
// 	printf("─────────────────\n");
// 	if (!content->config_lines)
// 	{
// 		printf("❌ No config lines found\n");
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (content->config_lines[i])
// 		{
// 			printf("[%d] %s", i, content->config_lines[i]);
// 			if (content->config_lines[i][strlen(content->config_lines[i])
// 				- 1] != '\n')
// 				printf("\n");
// 			i++;
// 		}
// 		printf("📊 Total config lines: %d\n", i);
// 	}
// 	printf("\n");
// 	printf("🗺️  MAP LINES:\n");
// 	printf("─────────────\n");
// 	if (!content->map_lines)
// 	{
// 		printf("❌ No map lines found\n");
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (content->map_lines[i])
// 		{
// 			printf("[%d] %s", i, content->map_lines[i]);
// 			if (content->map_lines[i][strlen(content->map_lines[i])
// 				- 1] != '\n')
// 				printf("\n");
// 			i++;
// 		}
// 		printf("📊 Total map lines: %d\n", i);
// 	}
// 	printf("\n📋 =========================\n");
// }

void	ft_validate_map(char *map_path, t_data *data, t_file_content *content)
{
	parse_cub_file(map_path, content, data);
	ft_check_config(content, data);
	ft_validate_map_structure(content, data);
	// print_file_content(content); // FOR TESTING
	// ft_validate_map_structure(content, data);
	// ft_free_file_content(content);
}
