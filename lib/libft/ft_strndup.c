#include "libft.h"

char	*ft_strndup(const char *string, size_t n)
{
	char	*res;
	char	*start;

	if (!n)
		return (NULL);
	res = (char *)malloc(n + 1);
	if (!res)
		return (NULL);
	start = res;
	while (*string && n-- > 0)
	{
		*res = *string;
		res++;
		string++;
	}
	*res = '\0';
	return (start);
}