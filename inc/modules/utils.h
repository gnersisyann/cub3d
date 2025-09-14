/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letto <letto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:11:03 by letto             #+#    #+#             */
/*   Updated: 2025/09/14 19:11:04 by letto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "validation.h"

void	init_structures(t_file_content *content, t_data *data);

void	ft_free_file_content(t_file_content *content);
void	ft_cleanup_data(t_data *data);
void	ft_cleanup_data_partial(t_data *data);

#endif