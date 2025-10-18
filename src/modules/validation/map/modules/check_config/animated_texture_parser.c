/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_texture_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:30:58 by ganersis          #+#    #+#             */
/*   Updated: 2025/10/18 18:33:50 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_identifier_length(char *line)
{
    char	*trimmed;

    trimmed = ft_skip_whitespace(line);
    if (ft_strncmp(trimmed, "DOC", 3) == 0 || ft_strncmp(trimmed, "DOO", 3) == 0)
        return (3);
    return (2);
}

static char	*extract_path_from_line(char *line)
{
    char	*path_start;
    char	*texture_path;
    int		identifier_len;

    identifier_len = get_identifier_length(line);
    path_start = ft_skip_whitespace(line);
    path_start += identifier_len;
    while (*path_start && (*path_start == ' ' || *path_start == '\t'))
        path_start++;
    if (!*path_start)
        return (NULL);
    texture_path = ft_strtrim(path_start, " \t\n");
    return (texture_path);
}

static char	*validate_and_extract_path(char *line, t_texture_context *ctx)
{
    char	*new_path;

    new_path = extract_path_from_line(line);
    if (!new_path)
        ft_error_exit_with_cleanup("Missing texture path", EXIT_FAILURE,
            ctx->data, ctx->content);
    if (!validate_texture_path(new_path))
    {
        free(new_path);
        ft_error_exit_with_cleanup("Invalid texture path", EXIT_FAILURE,
            ctx->data, ctx->content);
    }
    return (new_path);
}

static char	**reallocate_texture_array(char **old_array, int count,
        char *new_path, t_texture_context *ctx)
{
    char	**new_array;
    int		i;

    new_array = malloc(sizeof(char *) * (count + 1));
    if (!new_array)
    {
        free(new_path);
        ft_error_exit_with_cleanup("Memory allocation failed", EXIT_FAILURE,
            ctx->data, ctx->content);
    }
    i = -1;
    while (++i < count)
        new_array[i] = old_array[i];
    new_array[count] = new_path;
    if (old_array)
        free(old_array);
    return (new_array);
}

void	parse_animated_texture_line(char *line, char ***texture_paths,
        int *texture_count, t_texture_context *ctx)
{
    char	*new_path;

    new_path = validate_and_extract_path(line, ctx);
    *texture_paths = reallocate_texture_array(*texture_paths, *texture_count,
            new_path, ctx);
    (*texture_count)++;
}