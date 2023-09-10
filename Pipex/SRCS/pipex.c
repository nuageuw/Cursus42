/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:18:05 by aburnott          #+#    #+#             */
/*   Updated: 2022/11/09 23:24:50 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

int	main(int ac, char **av)
{
    (void) ac;
    (void) av;
	int	fd[2];
	int	id;
	int	x;
	int	y;
	
	if (pipe(fd) == -1)
	{
		printf("Error occured with open the pipe");
		return (1);
	}
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		printf("Input a number: ");
		scanf("%d", &x);
		write (fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return (0);
}