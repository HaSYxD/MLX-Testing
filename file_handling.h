/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:50:09 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:50:11 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HANDLING_H
# define FILE_HANDLING_H

void	normalise_data(t_data *data);
int		handle_obj(char *argv[], t_data *data);
int		check_user_input(int argc, char *argv[], t_data *data);

#endif
