/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-24 15:41:47 by mabdelha          #+#    #+#             */
/*   Updated: 2025/02/27 16:19:12 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_f = 0;

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_hand(int sig)
{
	(void)sig;
	g_f = 1;
}

void	ft_ch(char ch, int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((ch >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_f == 0)
			pause();
		g_f = 0;
	}
}

void	ft_str(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_ch(str[i], pid);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc == 3)
	{
		i = 0;
		pid = ft_atoi(argv[1]);
		ft_str(argv[2], pid);
		signal(SIGUSR1, ft_hand);
		signal(SIGUSR2, ft_hand);
		ft_ch('\0', pid);
	}
	else
	{
		write(1, "Usage: ./client <PID> <Message>\n", 32);
		return (1);
	}
}
