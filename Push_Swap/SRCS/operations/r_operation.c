/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_operation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:40:18 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/06 12:00:52 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	ra(t_node **head)
{
	rotate(head);
	write(1, "ra\n", 3);
}

void	rb(t_node **head)
{
	rotate(head);
	write(1, "rb\n", 3);
}

void	rr(t_node **head_a, t_node **head_b)
{
	rotate(head_a);
	rotate(head_b);
	write(1, "rr\n", 3);
}
