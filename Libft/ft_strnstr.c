/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:03:58 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/06 15:59:57 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((s1 == NULL || s2 == NULL) && n == 0)
		return (0);
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] && n > 0)
	{
		j = 0;
		while (s1[i + j] == s2[j] && s1[i + j] && i + j < n)
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (0);
}
