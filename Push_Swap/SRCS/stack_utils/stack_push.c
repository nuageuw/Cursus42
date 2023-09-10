/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:55:03 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/11 13:47:16 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	stack_push(t_stack *stack, int value)
{
	t_node	*new;
	t_node	*temp;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		exit(EXIT_FAILURE);
	new->o_value = value;
	new->value = 0;
	new->next = 0;
	temp = stack->head;
	if (!temp)
		stack->head = new;
	else
	{
		while (temp && temp->next)
			temp = temp->next;
		temp->next = new;
	}
	stack->size++;
	return (1);
}
