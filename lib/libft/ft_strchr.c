/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luminous <luminous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:41:12 by luminous          #+#    #+#             */
/*   Updated: 2025/07/04 16:41:13 by luminous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*offset;
	unsigned char	target;

	target = (unsigned char)c;
	offset = (char *)s;
	while (*offset)
	{
		if (*offset == target)
			return (offset);
		offset++;
	}
	if (target == '\0')
		return (offset);
	return (NULL);
}
