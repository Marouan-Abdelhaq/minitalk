/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-22 21:30:51 by mabdelha          #+#    #+#             */
/*   Updated: 2025-02-22 21:30:51 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	g_pid;
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

void	ft_ch(char ch, int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		g_pid = 0;
		if ((ch >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		while (g_pid == 0)
			usleep(200);
	}
}

void	ft_hand(int sig)
{
	if (sig == SIGUSR1)
		g_pid = 1;
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
	ft_ch('\0', pid);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid < 0)
		{
			write(1, "Invalid PID\n", 12);
			return (1);
		}
		signal(SIGUSR1, ft_hand);
		ft_str(argv[2], pid);
	}
	else
	{
		write(1, "Usage: ./client <PID> <Message>\n", 32);
		return (1);
	}
}
