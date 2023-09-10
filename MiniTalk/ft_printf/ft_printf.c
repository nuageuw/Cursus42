/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:27:10 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/27 16:15:29 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_format(va_list arg, char c, int *len)
{
	if (c == 'c')
		*len += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		*len += ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		*len += ft_void_hexa(va_arg(arg, void *), 1);
	else if (c == 'i' || c == 'd')
		*len += ft_putnbr(va_arg(arg, int), 1);
	else if (c == 'u')
		*len += ft_putnbr(va_arg(arg, unsigned int), 1);
	else if (c == 'x')
		*len += ft_hexa(va_arg(arg, unsigned int), 0, 1);
	else if (c == 'X')
		*len += ft_hexa(va_arg(arg, unsigned int), 0, 2);
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

	va_start(arg, s);
	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			check_format(arg, s[++i], &len);
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
