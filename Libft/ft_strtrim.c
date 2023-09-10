/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:11:07 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/11 15:57:55 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1)
		return (0);
	if (!set)
		ft_strdup(s1);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && !(check_set(s1[start], set)))
		start++;
	while (end > start && !(check_set(s1[end - 1], set)))
		end--;
	trim = ft_substr(s1, start, end - start);
	return (trim);
}
