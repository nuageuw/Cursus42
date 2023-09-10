/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:07:49 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/21 14:43:22 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*mappied;

	if (!s || !f)
		return (0);
	i = 0;
	mappied = malloc(sizeof(*mappied) * (ft_strlen(s)) + 1);
	if (!mappied)
		return (0);
	while (s[i])
	{
		mappied[i] = (*f)(i, s[i]);
		i++;
	}
	mappied[i] = '\0';
	return (mappied);
}
