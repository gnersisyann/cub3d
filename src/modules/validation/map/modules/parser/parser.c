#include "error.h"
#include "libft.h"
#include "validation.h"

void	parse_cub_file(char *filename, t_file_content *content, t_data *data)
{
	char **file_lines;

	file_lines = parse_file(filename, data, content);
	if (!file_lines)
		ft_error_exit_with_cleanup("Failed to parse file", EXIT_FAILURE, data,
			content);

	ft_split_file_content(file_lines, content, data);

	ft_free_array(file_lines);
}