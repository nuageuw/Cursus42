/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:17:05 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/14 19:02:27 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;
	int				temp;

	i = 0;
	sign = 1;
	res = 0;
	temp = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++temp)
		res = res * 10 + str[i++] - 48;
	if ((res >= 9223372036854775807 || temp >= 20) && sign == 1)
		return (-1);
	else if ((res > 9223372036854775807 || temp >= 20) && sign == -1)
		return (0);
	return (sign * res);
}
