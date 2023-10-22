/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:46:27 by romvan-d          #+#    #+#             */
/*   Updated: 2023/08/07 16:11:36 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "cub3d.h"

/* Movements */

void	forward_movement(t_cube *cube);
void	backward_movement(t_cube *cube);
void	left_movement(t_cube *cube);
void	right_movement(t_cube *cube);

/* Rotations */

void	rotate_left(t_cube *cube);
void	rotate_right(t_cube *cube);
#endif