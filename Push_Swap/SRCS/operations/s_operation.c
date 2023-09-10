/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_operation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:25:39 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/11 14:02:13 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	sa(t_node *head)
{
	ft_swap(head);
	write(1, "sa\n", 3);
}

void	sb(t_node *head)
{
	ft_swap(head);
	write(1, "sb\n", 3);
}

void	ss(t_node *head_a, t_node *head_b)
{
	ft_swap(head_a);
	ft_swap(head_b);
	write(1, "ss\n", 3);
}
