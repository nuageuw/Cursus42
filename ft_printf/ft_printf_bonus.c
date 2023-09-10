/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:27:10 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/29 01:10:16 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	check_flag(char c, t_type *flag)
{
	if (c == '#')
		flag->hashtag = 1;
	else if (c == ' ')
		flag->space = 1;
	else if (c == '+')
		flag->plus = 1;
	else
		return (0);
	return (1);
}

static void	check_format(va_list arg, char c, int *len, t_type *flag)
{
	if (c == 'c')
		*len += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		*len += ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		*len += ft_void_hexa(va_arg(arg, void *), 1, flag);
	else if (c == 'i' || c == 'd')
		*len += ft_putnbr(va_arg(arg, int), 1, flag);
	else if (c == 'u')
		*len += ft_putnbr(va_arg(arg, unsigned int), 1, flag);
	else if (c == 'x')
		*len += ft_hexa(va_arg(arg, unsigned int), 0, 1, flag);
	else if (c == 'X')
		*len += ft_hexa(va_arg(arg, unsigned int), 0, 2, flag);
	else if (c == '%')
		*len += ft_putchar('%');
	else
		*len += ft_putchar(c);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		len;
	int		i;
	t_type	flag;

	flag.hashtag = 0;
	flag.plus = 0;
	flag.space = 0;
	va_start(arg, s);
	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			if (!check_flag(s[++i], &flag))
				check_format(arg, s[i], &len, &flag);
			else
				check_format(arg, s[++i], &len, &flag);
		}
		else
			len += ft_putchar(s[i]);
	}
	va_end(arg);
	return (len);
}
