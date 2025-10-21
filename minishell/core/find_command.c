/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:40:35 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 14:07:33 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strcat_pp(t_hub *hub, char *path, char *cmd)
{
	int		i;
	int		j;
	char	*cmd_path;

	cmd_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!cmd_path)
		return (ft_error("cmd_path", strerror(errno)), ft_exit(hub, 1), NULL);
	i = -1;
	while (path[++i])
		cmd_path[i] = path[i];
	cmd_path[i] = '/';
	i++;
	j = 0;
	while (cmd[j] && cmd[j] == ' ')
		j++;
	while (cmd[j] && cmd[j] != ' ')
	{
		cmd_path[i] = cmd[j];
		j++;
		i++;
	}
	cmd_path[i] = 0;
	return (cmd_path);
}

static int	direct_path(t_ppl *ppl, char **args)
{
	if (access(args[0], F_OK) != 0)
		return (ppl->error = 127, ft_error(args[0], strerror(errno)), 127);
	if (access(args[0], X_OK) != 0)
		return (ppl->error = 126, ft_error(args[0], strerror(errno)), 126);
	ppl->path_name = ft_strdup(args[0]);
	if (!ppl->path_name)
		return (ppl->error = 1, ft_error("path_name", strerror(errno)), 1);
	return (0);
}

int	find_command(t_hub *hub, t_ppl *ppl, char **args)
{
	int	i;

	if (!args)
		return (0);
	if (ft_strchr(args[0], '/'))
		return (direct_path(ppl, args));
	if (verif_built_in(args[0]) == 0)
		return (0);
	if (args[0][0] == '\0')
		return (ppl->error = 127, ft_error(" ", "command not found"), 127);
	i = 0;
	if (!ppl->paths)
		return (ft_error(args[0], "command not found"), ppl->error = 127, 127);
	while (ppl->paths[i])
	{
		ppl->path_name = ft_strcat_pp(hub, ppl->paths[i], args[0]);
		if (!ppl->path_name)
			return (ft_error("path_name", strerror(errno)), ft_exit(hub, 1), 1);
		if (access(ppl->path_name, X_OK) == 0)
			return (0);
		free(ppl->path_name);
		ppl->path_name = NULL;
		i++;
	}
	return (ft_error(args[0], "command not found"), ppl->error = 127, 127);
}
