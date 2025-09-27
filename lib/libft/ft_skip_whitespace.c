#include "libft.h"

char	*ft_skip_whitespace(char *str)
{
    if (!str)
        return (NULL);
    while (*str && (*str == ' ' || *str == '\t'))
        str++;
    return (str);
}