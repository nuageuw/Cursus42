/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:47:57 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/05 17:33:08 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	count;

	i = ft_strlen(src);
	count = 0;
	if (!src)
		return (0);
	if (i + 1 < n)
	{
		count = -1;
		while (++count < i + 1)
			dst[count] = src[count];
	}
	else if (n)
	{
		count = -1;
		while (++count < n - 1)
			dst[count] = src[count];
		dst[count] = '\0';
	}
	return (i);
}
