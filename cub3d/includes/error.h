/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:39:18 by aburnott          #+#    #+#             */
/*   Updated: 2023/10/03 17:33:55 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	error(t_cube *cub, char *str, int code);
void	ft_free_end(t_cube *cub);
void	ft_free(char **str, char *line);
void	check_value(t_cube *cube);

#endif