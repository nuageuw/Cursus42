/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:13:38 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/12 10:31:24 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_node
{
	int				o_value;
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	int		size;
}	t_stack;

t_stack	*stack_init(void);
int		stack_push(t_stack *stack, int value);
int		ft_atoi(const char *str, int *check);
void	ft_swap(t_node *head);
void	rotate(t_node **head);
void	reverse_rotate(t_node **head);
void	push(t_node **head_1, t_node **head_2);
char	**ft_split(char const *s, char c);
void	pa(t_stack *stack, t_node **head_a, t_node **head_b);
void	pb(t_stack *stack, t_node **head_a, t_node **head_b);
void	ra(t_node **head);
void	rb(t_node **head);
void	rr(t_node **head_a, t_node **head_b);
void	rra(t_node **head);
void	rrb(t_node **head);
void	rrr(t_node **head_a, t_node **head_b);
void	sa(t_node *head);
void	sb(t_node *head);
void	ss(t_node *head_a, t_node *head_b);
void	algo(t_stack *stack_a, t_stack *stack_b);
int		check_sorted(t_stack *stack_a);
void	sort_five(t_stack *stack_a, t_stack *stack_b);
void	sort_three(t_stack *stack_a);
void	ft_free(t_stack *stack_a, t_stack *stack_b);
void	ft_free_arr(char **arr);

#endif