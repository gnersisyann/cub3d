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
