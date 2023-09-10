/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:02:50 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/15 16:26:37 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signum)
{
	static char	buf[500];
	static int	buf_index = 0;
	static char	current_char = 0;
	static int	bits_received = 0;

	current_char += (signum == SIGUSR1);
	bits_received++;
	if (bits_received == 8)
	{
		buf[buf_index] = current_char;
		buf_index++;
		if (current_char == '\0' || buf_index == 500)
		{
			write(1, buf, buf_index);
			buf_index = 0;
		}
		bits_received = 0;
		current_char = 0;
	}
	else
		current_char = current_char << 1;
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	ft_printf("Waiting for message...\n");
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
