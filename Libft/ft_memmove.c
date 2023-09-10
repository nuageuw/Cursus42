/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:39:24 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/06 14:29:47 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char	*cpy_dest;
	char	*cpy_src;
	size_t	i;

	cpy_dest = (char *)dest;
	cpy_src = (char *)src;
	if (!dest && !src)
		return (0);
	i = 0;
	if (cpy_src < cpy_dest)
	{
		i = n - 1;
		while (i < n)
		{
			cpy_dest[i] = cpy_src[i];
			i--;
		}
		return (dest);
	}
	while (i < n)
	{
		cpy_dest[i] = cpy_src[i];
		i++;
	}
	return (dest);
}
