/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:22:17 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/11 15:37:30 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

static int	get_iteration(t_stack *stack_a)
{
	t_node	*head;
	int		max_ite;
	int		max;

	head = stack_a->head;
	max = head->value;
	max_ite = 0;
	while (head)
	{
		if (head->value > max)
			max = head->value;
		head = head->next;
	}
	while ((max >> max_ite) != 0)
		max_ite++;
	return (max_ite);
}

static void	radix(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	max_bits;
	int	i;
	int	j;
	int	value;

	size = stack_a->size;
	max_bits = get_iteration(stack_a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			value = stack_a->head->value;
			if (((value >> i) & 1) == 1)
				ra(&stack_a->head);
			else
				pb(stack_b, &stack_a->head, &stack_b->head);
		}
		while (stack_b->size != 0)
			pa(stack_b, &stack_a->head, &stack_b->head);
		i++;
	}
}

void	algo(t_stack *stack_a, t_stack *stack_b)
{	
	if (stack_a->size <= 3)
		sort_three(stack_a);
	else if (stack_a->size <= 5)
		sort_five(stack_a, stack_b);
	else
		radix(stack_a, stack_b);
	return ;
}
