/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:31:20 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/11 15:09:05 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	transform(t_stack *stack)
{
	t_node	*tmp;
	t_node	*tmp_bis;

	tmp = stack->head;
	while (tmp)
	{
		tmp_bis = stack->head;
		while (tmp_bis)
		{
			if (tmp_bis->o_value < tmp->o_value)
				++tmp->value;
			tmp_bis = tmp_bis->next;
		}
		tmp = tmp->next;
	}
}

static int	check_stack(t_stack *stack_a, int ato)
{
	t_node	*current;

	current = stack_a->head;
	while (current && current->o_value != ato)
		current = current->next;
	if (current)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	return (0);
}

static void	valid_stack(t_stack *stack_a, char **list, int i)
{
	int	check;
	int	ato;

	check = 0;
	while (list[i])
	{
		ato = ft_atoi(list[i], &check);
		check_stack(stack_a, ato);
		stack_push(stack_a, ato);
		if (check)
		{
			write (2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	transform(stack_a);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**splitted;

	if (ac == 1)
		return (0);
	stack_a = stack_init();
	stack_b = stack_init();
	if (ac == 2)
	{
		splitted = ft_split(av[1], ' ');
		if (!splitted)
			exit(EXIT_FAILURE);
		valid_stack(stack_a, splitted, 0);
		ft_free_arr(splitted);
	}
	else
		valid_stack(stack_a, av, 1);
	if (!check_sorted(stack_a))
		algo(stack_a, stack_b);
	ft_free(stack_a, stack_b);
	return (0);
}
