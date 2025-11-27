/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:10:49 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:10:50 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../structs.h"

void	ft_error_exit(char *message, int exit_code);
void	ft_error_exit_with_cleanup(char *message, int exit_code, t_data *data,
			t_file_content *content);

#endif
