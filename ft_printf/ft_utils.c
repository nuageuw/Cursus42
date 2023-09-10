/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:14:24 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/26 13:37:43 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i++;
	write (1, s, i);
	return (i);
}

int	ft_putnbr(long nb, int len)
{
	if (nb < 0)
	{
		write(1, "-", 1);
		len++;
		nb *= -1;
	}
	if (nb > 9)
	{
		len += ft_putnbr(nb / 10, 1);
		nb %= 10;
	}
	if (nb <= 9)
	{
		nb += 48;
		write (1, &nb, 1);
	}
	return (len);
}

int	ft_hexa(unsigned long hex, int len, int type)
{
	if (hex >= 16)
		len += ft_hexa(hex / 16, 0, type);
	hex %= 16;
	if (hex >= 10)
	{
		if (type == 1)
			hex += 87;
		else
			hex += 55;
		write (1, &hex, 1);
		len++;
	}
	else
	{
		hex += 48;
		write (1, &hex, 1);
		len++;
	}
	return (len);
}

int	ft_void_hexa(void *p, int type)
{
	int	len;

	len = 0;
	write (1, "0x", 2);
	len += 2;
	if ((unsigned long)p == 0)
	{
		write (1, "0", 1);
		len += 1;
	}
	else
		len += ft_hexa((unsigned long)p, 0, type);
	return (len);
}
