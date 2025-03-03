/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-24 17:25:28 by mabdelha          #+#    #+#             */
/*   Updated: 2025/02/27 16:17:59 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
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
		write(1, &c, 1);
	}
}

void	ft_hand(int sig, siginfo_t *info, void *ca)
{
	static int	i = 0;
	static char	c = 0;

	(void)ca;
	if (sig == SIGUSR1)
		c |= (1 << (7 - i));
	i++;
	if (i == 8)
	{
		usleep(100);
		if (c)
			write(1, &c, 1);
		else
			(write(1, "\n", 1), kill(info->si_pid, SIGUSR2));
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int			pid;
	struct sigaction	sig;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	sig.sa_sigaction = ft_hand;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	if (sigaction(SIGUSR1, &sig, 0) == -1 || sigaction(SIGUSR2, &sig, 0) == -1)
	{
		write(1, "Error: sigaction failed\n", 24);
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
