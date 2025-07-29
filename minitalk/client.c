/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:31:46 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/26 15:43:34 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <signal.h>

static int	is_pid_valid(const char *pid_str)
{
	int	i;

	i = 0;
	if (!pid_str || pid_str[0] == '\0')
		return (0);
	while (pid_str[i])
	{
		if (pid_str[i] < '0' || pid_str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_pid_errors(const char *pid_str)
{
	pid_t	pid;

	if (!is_pid_valid(pid_str))
	{
		ft_putstr_fd("error: invalid or missing PID\n", 2);
		return (-1);
	}
	pid = ft_atoi(pid_str);
	if (pid <= 0)
	{
		ft_putstr_fd("error: invalid PID, must be > 0\n", 2);
		return (-1);
	}
	if (kill(pid, 0) == -1)
	{
		if (errno == ESRCH)
			ft_putstr_fd("error: PID doesnt exist\n", 2);
		else if (errno == EPERM)
			ft_putstr_fd("error: permission denied\n",
				2);
		else
			ft_putstr_fd("error: indentification incorrect.\n", 2);
		return (-1);
	}
	return (pid);
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	i;
	int	res;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			res = kill(pid, SIGUSR2);
		else
			res = kill(pid, SIGUSR1);
		if (res == -1)
		{
			ft_putstr_fd("error: impossible to communicate\n", 2);
			_exit(1);
		}
		usleep(100);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr_fd("error: usage = ./client [PID] [message]\n", 2);
		return (1);
	}
	pid = check_pid_errors(argv[1]);
	if (pid == -1)
		return (1);
	while (argv[2][i])
	{
		send_char(pid, argv[2][i]);
		i++;
	}
	send_char(pid, '\0');
	send_char(pid, '\n');
	return (0);
}
