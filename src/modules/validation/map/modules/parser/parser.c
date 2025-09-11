#include "error.h"
#include "libft.h"
#include "validation.h"

void	parse_cub_file(char *filename, t_file_content *content)
{
	char	**file_lines;

	file_lines = parse_file(filename);
	if (!file_lines)
		ft_error_exit("Failed to parse file", EXIT_FAILURE);
	
	ft_split_file_content(file_lines, content);
	ft_free_array(file_lines);
}
