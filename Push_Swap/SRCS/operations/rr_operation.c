/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:43:09 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/09 19:11:52 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	rra(t_node **head)
{
	reverse_rotate(head);
	write(1, "rra\n", 4);
}

void	rrb(t_node **head)
{
	reverse_rotate(head);
	write(1, "rrb\n", 4);
}

void	rrr(t_node **head_a, t_node **head_b)
{
	reverse_rotate(head_a);
	reverse_rotate(head_b);
	write(1, "rrr\n", 4);
}
