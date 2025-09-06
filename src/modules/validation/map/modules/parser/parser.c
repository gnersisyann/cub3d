#include "error.h"
#include "libft.h"
#include "validation.h"

t_file_content	*parse_cub_file(char *filename)
{
	char			**file_lines;
	t_file_content	*content;

	file_lines = parse_file(filename);
	if (!file_lines)
		ft_error_exit("Failed to parse file", EXIT_FAILURE);
	
	content = ft_split_file_content(file_lines);
	ft_free_array(file_lines);
	return (content);
}
