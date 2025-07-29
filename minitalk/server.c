/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:31:17 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/26 15:41:00 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <errno.h>
#include <signal.h>

static void	recept_signal(int sig)
{
	static unsigned char	c = 0;
	static int				bits = 0;

	if (sig == SIGUSR1)
		c = (c << 1) | 0;
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	bits++;
	if (bits == 8)
	{
		write(1, &c, 1);
		bits = 0;
		c = 0;
	}
}

static int	check_server_permissions(void)
{
	if (kill(getpid(), 0) == -1)
	{
		if (errno == EPERM)
			ft_putstr_fd("error: acces denied\n", 2);
		else
			ft_putstr_fd("error\n", 2);
		return (1);
	}
	return (0);
}

int	main(void)
{
	__pid_t	pid;

	pid = getpid();
	ft_putstr_fd("server's PID =", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	if (check_server_permissions())
		return (1);
	if (signal(SIGUSR1, recept_signal) == SIG_ERR || signal(SIGUSR2,
			recept_signal) == SIG_ERR)
	{
		ft_putstr_fd("error\n", 2);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
