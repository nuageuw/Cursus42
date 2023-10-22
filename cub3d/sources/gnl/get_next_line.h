/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:08:01 by aburnott          #+#    #+#             */
/*   Updated: 2023/09/21 15:05:32 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../includes/utils.h"

char	*free_all(char *save, char *buf);
int		search_n(char *save);
char	*ft_strjoin(char *save, char *buf, int buf_len);
char	*get_next_line(int fd);
int		ft_strlen(char *s);

#endif