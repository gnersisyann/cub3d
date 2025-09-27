/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <ganersis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:50:26 by ganersis          #+#    #+#             */
/*   Updated: 2025/09/27 16:50:26 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_whitespace(char *str)
{
	char	*end;
	char	*start;

	if (!str)
		return (NULL);
	start = ft_skip_whitespace(str);
	if (!*start)
		return (start);
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return (start);
}
