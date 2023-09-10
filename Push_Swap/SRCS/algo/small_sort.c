/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:24:41 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/12 10:33:37 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

int	check_sorted(t_stack *stack_a)
{
	t_node	*current;

	current = stack_a->head;
	if (stack_a->head == NULL)
		return (1);
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void	sort_three(t_stack *stack_a)
{
	int	checked;

	checked = check_sorted(stack_a);
	while (!checked)
	{
		checked = check_sorted(stack_a);
		if (stack_a->head->value > stack_a->head->next->value)
			sa(stack_a->head);
		if (stack_a->size == 3
			&& stack_a->head->next->value > stack_a->head->next->next->value)
			rra(&stack_a->head);
	}
}

static void	empty_stack_b(t_stack *stack_a, t_stack *stack_b)
{
	while (stack_b->size != 1)
	{
		if (stack_b->head->value > stack_b->head->next->value)
			pa(stack_b, &stack_a->head, &stack_b->head);
		else
			rrb(&stack_b->head);
	}
	pa(stack_b, &stack_a->head, &stack_b->head);
}

static int	min_index(t_stack *stack_a)
{
	t_node	*min;
	t_node	*tmp;

	min = stack_a->head;
	tmp = stack_a->head->next;
	while (tmp)
	{
		if (min->value > tmp->value)
			min = tmp;
		tmp = tmp->next;
	}
	return (min->value);
}

void	sort_five(t_stack *stack_a, t_stack *stack_b)
{
	int		min;
	t_node	*tmp;

	while (stack_a->size != 3)
	{
		min = min_index(stack_a);
		tmp = stack_a->head;
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->value == min)
			rra(&stack_a->head);
		while (stack_a->head->value != min)
			ra(&stack_a->head);
		pb(stack_b, &stack_a->head, &stack_b->head);
		stack_a->size--;
	}
	sort_three(stack_a);
	empty_stack_b(stack_a, stack_b);
}
