/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:28:19 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/13 11:39:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

int		check_file(char *file, t_cube *cub);
int		get_map_size(char *line, t_cube *cub);
int		store_map(char *file, t_cube *cub);
int		check_map(t_cube *cub);
char	*parse_texture(char *path);
void	set_color(t_cube *cub, char *line, int type);
void	init_struc(char *av);
void	check_texture(t_cube *cub);
void	call_suite(t_cube *cub, char *file);

#endif