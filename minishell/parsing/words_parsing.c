/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 09:38:19 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 21:07:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_valid_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != END)
	{
		if (tokens->str && ft_strlen(tokens->str) > 0)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	fill_args(t_token **tokens, t_cmd *cmd, t_hub *hub)
{
	t_token	*tok;
	int		count;
	int		i;

	count = count_valid_tokens(*tokens);
	if (count == 0)
		return (cmd->args = NULL, (void)0);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		return (ft_exit(hub, 1));
	tok = *tokens;
	i = 0;
	while (tok && tok->type != END)
	{
		if (tok->str && ft_strlen(tok->str) > 0)
			cmd->args[i++] = ft_strdup(tok->str);
		tok = tok->next;
	}
	cmd->args[i] = NULL;
}

void	free_str_tab(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
