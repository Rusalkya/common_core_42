/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:20:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:47:57 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirection_token(char *token)
{
	return (ft_strcmp_equal(token, "<") == 0
		|| ft_strcmp_equal(token, ">") == 0
		|| ft_strcmp_equal(token, ">>") == 0
		|| ft_strcmp_equal(token, "<<") == 0);
}

static int	count_non_redirect_args(char **tokens)
{
	int	i;
	int	total_args;

	total_args = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]) && tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		total_args++;
		i++;
	}
	return (total_args);
}

static void	fill_args_array(char **tokens, char **new_args)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]) && tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		new_args[arg_count] = ft_strdup(tokens[i]);
		arg_count++;
		i++;
	}
	new_args[arg_count] = NULL;
}

void	process_tokens(t_cmd *cmd, char **tokens)
{
	int		total_args;
	char	**new_args;

	total_args = count_non_redirect_args(tokens);
	new_args = malloc(sizeof(char *) * (total_args + 1));
	if (!new_args)
		return ;
	fill_args_array(tokens, new_args);
	if (cmd->args)
		free_str_tab(cmd->args);
	cmd->args = new_args;
}

char	*find_command_in_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]) && tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		return (tokens[i]);
	}
	return (NULL);
}
