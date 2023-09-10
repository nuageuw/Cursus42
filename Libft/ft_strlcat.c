/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:10:42 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/06 17:44:08 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;

	if ((dst == 0 || src == 0) && n == 0)
		return (0);
	i = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	j = dest_len;
	if (n == 0 || n <= dest_len)
		return (src_len + n);
	while (src[i] && i < n - dest_len - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dest_len + src_len);
}
