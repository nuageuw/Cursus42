/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:59:59 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/22 16:34:52 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

void	ft_putstr(char *str, int fd);
char	*ft_strdup(char *s, int start, int end);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_malloc(size_t size);
char	*ft_strdup_modif(char *s, int start, int end);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str, int type);
void	ft_swap_double(double *x, double *y);

#endif