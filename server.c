/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 22:05:56 by mabdelha          #+#    #+#             */
/*   Updated: 2025-02-22 22:05:56 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(2, "-2147483648", 11);
	}
	else if (n < 0)
	{
		write(2, "-", 1);
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(2, &c, 1);
	}
}

void	ft_hand(int sig, siginfo_t *info, void *ca)
{
	static int	i;
	static char	c;
	static int	pid;

	(void)ca;
	if (pid != info->si_pid)
	{
		i = 0;
		c = 0;
		pid = info->si_pid;
	}
	if (sig == SIGUSR1)
		c |= (1 << (7 - i));
	i++;
	if (i == 8)
	{
		if (c != '\0')
			(write(1, &c, 1), i = 0, c = 0);
		else
			write(1, "\n", 1);
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	pid = getpid();
	ft_putnbr(pid);
	write(2, "\n", 1);
	sig.sa_sigaction = ft_hand;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	while (1)
	{
		pause();
	}
}
