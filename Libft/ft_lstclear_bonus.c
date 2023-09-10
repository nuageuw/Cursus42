/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:19:43 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/11 15:37:45 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tab;

	if (!lst || !del)
	{
		return ;
	}
	while (*lst)
	{
		tab = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tab;
	}
	*lst = 0;
}
