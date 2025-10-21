/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:46:51 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 14:05:53 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	verif_long_long_2(char *nbr)
{
	int		i;
	int		j;
	char	*lg_lg;

	i = 0;
	j = 0;
	lg_lg = "9223372036854775807";
	if (nbr[i] == '+')
		lg_lg = "+9223372036854775807";
	while (nbr[i] && lg_lg[i])
	{
		if (nbr[i] > lg_lg[i])
			j++;
		i++;
	}
	if ((lg_lg[i] == 0 && j > 0) || (lg_lg[i] == 0 && nbr[i] != 0))
		return (1);
	return (0);
}

static int	verif_long_long(char *nbr)
{
	int		i;
	int		j;
	char	*lg_lg_ng;

	i = 0;
	j = 0;
	lg_lg_ng = "-9223372036854775808";
	if (nbr[i] == '-')
	{
		while (nbr[i] && lg_lg_ng[i])
		{
			if (nbr[i] > lg_lg_ng[i])
				j++;
			i++;
		}
		if ((lg_lg_ng[i] == 0 && j > 0) || (lg_lg_ng[i] == 0 && nbr[i] != 0))
			return (1);
		return (0);
	}
	return (verif_long_long_2(nbr));
}

static long long	ft_atoi_2(char *src)
{
	int			i;
	int			s;
	long long	result;

	i = 0;
	s = 0;
	if (src[i] == '-')
		s = 1;
	if (src[i] == '-' || src[i] == '+')
		i++;
	result = 0;
	while (src[i] >= '0' && src[i] <= '9')
	{
		result = result * 10 + (src[i] - '0');
		i++;
	}
	if (s == 1)
		return (result * -1);
	return (result);
}

static int	nbr_exit(t_hub *hub, char *nbr)
{
	int	i;

	i = 0;
	if (nbr == NULL)
		return (0);
	if (hub->cmd->args[1][0] == 0)
		return (hub->last_value = 2,
			ft_error("exit", "numeric argument required"), 0);
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i] >= '0' && nbr[i] <= '9')
		i++;
	if (nbr[i])
		return (hub->last_value = 2,
			ft_error("exit", "numeric argument required"), 0);
	if (verif_long_long(nbr) != 0)
		return (hub->last_value = 2,
			ft_error("exit", "numeric argument required"), 0);
	if (hub->cmd->args[2] != NULL)
		return (ft_error("exit", "too many arguments"), 1);
	hub->last_value = (unsigned char)ft_atoi_2(nbr);
	return (0);
}

int	ft_exit_bi(t_hub *hub)
{
	int	nb_error;

	ft_printf(2, "exit\n");
	hub->ppl->error = 0;
	if (nbr_exit(hub, hub->cmd->args[1]) == 1)
		return (1);
	nb_error = hub->last_value;
	rl_clear_history();
	if (hub->info)
		free_info(hub->info);
	if (hub->cmd)
		free_cmd(hub->cmd);
	if (hub->ppl)
		free_ppl(hub->ppl);
	if (hub->token)
		free_token(hub->token);
	if (hub->rl)
		free_rl(hub->rl);
	if (hub->quote)
		free(hub->quote);
	free(hub);
	exit(nb_error);
	return (0);
}
