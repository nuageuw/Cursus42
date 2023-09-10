/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_flag_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:24:03 by aburnott          #+#    #+#             */
/*   Updated: 2022/10/27 10:59:13 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_put_hex(int type, t_type *flag)
{	
	if (type == 1)
	{
		write (1, "0x", 2);
		flag->hashtag = 0;
		return (2);
	}
	else if (type == 2)
	{
		write(1, "0X", 2);
		flag->hashtag = 0;
		return (2);
	}
	return (0);
}

int	ft_put_sp(t_type *flag)
{
	if (flag->plus)
	{
		write(1, "+", 1);
		flag->plus = 0;
		return (1);
	}
	else if (flag->space)
	{
		write (1, " ", 1);
		flag->space = 0;
		return (1);
	}
	return (0);
}
