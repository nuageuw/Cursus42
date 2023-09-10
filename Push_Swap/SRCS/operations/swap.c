/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:55:02 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/11 14:09:49 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	ft_swap(t_node *head)
{
	int	temp;

	temp = head->value;
	head->value = head->next->value;
	head->next->value = temp;
}

void	rotate(t_node **head)
{
	t_node	*temp;
	t_node	*list;

	temp = *head;
	*head = (*head)->next;
	if (!*head)
		return ;
	list = *head;
	while (list->next)
		list = list->next;
	list->next = temp;
	temp->next = 0;
}

void	reverse_rotate(t_node **head)
{
	t_node	*temp;
	t_node	*list;

	list = *head;
	while (list->next->next)
		list = list->next;
	temp = list->next;
	list->next = 0;
	temp->next = *head;
	*head = temp;
}

void	push(t_node **head_1, t_node **head_2)
{
	t_node	*temp;

	temp = *head_1;
	*head_1 = (*head_1)->next;
	temp->next = *head_2;
	*head_2 = temp;
}
