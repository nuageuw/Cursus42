/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:58:01 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/11 11:44:42 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_len(long n)
{
	long	size;

	size = 1;
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

void	convert(char *s, int len, long n, int isn)
{
	while (len >= isn)
	{
		s[len] = (n % 10 + '0');
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{	
	int		len;
	char	*res;
	int		is_negative;
	long	ln;

	ln = n;
	is_negative = 0;
	len = ln < 0;
	if (ln < 0)
	{
		is_negative = 1;
		ln *= -1;
	}
	len += calc_len(ln);
	res = malloc(sizeof(*res) * len + 1);
	if (!res)
		return (0);
	if (is_negative)
		res[0] = '-';
	res[len] = '\0';
	len--;
	convert(res, len, ln, is_negative);
	return (res);
}
