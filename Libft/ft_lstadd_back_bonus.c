/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:50:40 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/11 12:08:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{	
	t_list	*tab;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		tab = ft_lstlast(*lst);
		tab->next = new;
	}
}
