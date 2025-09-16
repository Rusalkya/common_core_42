/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 09:38:19 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 15:50:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	have_a_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

void fill_args(t_token **tokens, t_command *cmd)
{
    t_token *tok;
    int count = 0;
    int i = 0;

    tok = *tokens;
    while (tok && tok->type != END)
    {
        count++;
        tok = tok->next;
    }

    cmd->args = malloc(sizeof(char *) * (count + 2)); // command + args + NULL
    if (!cmd->args)
        return;

    cmd->args[0] = ft_strdup(cmd->command); // ex: "ls"
    tok = *tokens;
    i = 1;
    while (tok && tok->type != END)
    {
        cmd->args[i++] = ft_strdup(tok->str);
        tok = tok->next;
    }
    cmd->args[i] = NULL;
}


void free_str_tab(char **strs)
{
    int i = 0;
    if (!strs)
        return;
    while (strs[i])
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}
