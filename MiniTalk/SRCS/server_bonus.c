/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:02:50 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/16 10:41:13 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	send_ack(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void	signal_handler(int signum, siginfo_t *info, void *ptr)
{
	static char	buf[500];
	static int	buf_index = 0;
	static char	current_char = 0;
	static int	bits_received = 0;

	(void) *ptr;
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
			if (current_char == '\0')
				send_ack(info->si_pid);
		}
		bits_received = 0;
		current_char = 0;
	}
	else
		current_char = current_char << 1;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	ft_printf("Waiting for message...\n");
	while (1)
		pause();
	return (0);
}
