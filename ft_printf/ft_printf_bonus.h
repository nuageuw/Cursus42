/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:56:19 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/27 10:54:06 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_type
{
	int	space;
	int	hashtag;
	int	plus;
}			t_type;

int	ft_printf(const char *s, ...);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(long nb, int len, t_type *type);
int	ft_hexa(unsigned long hex, int len, int type, t_type *flag);
int	ft_void_hexa(void *p, int type, t_type *flag);
int	ft_put_hex(int type, t_type *flag);
int	ft_put_sp(t_type *flag);

#endif