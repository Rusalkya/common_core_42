/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:01:50 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/13 14:35:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*lst_new_token(char *value, int type, t_hub *hub)
{
	t_token	*token;

	(void)hub;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = value;
	token->str_backup = NULL;
	token->var_exists = false;
	token->type = type;
	token->status = DEFAULT;
	token->join = false;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	lst_add_back_token(t_token **lst, t_token *new_tok)
{
	t_token	*tmp;

	if (!*lst)
		*lst = new_tok;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_tok;
	}
}

void	lstclear_token(t_token **lst)
{
	if (!lst)
		return ;
	*lst = NULL;
}

char	**realloc_tab(char **old, char *new_str, int count, t_hub *hub)
{
	char	**new_tab;
	int		i;

	i = 0;
	(void)hub;
	new_tab = malloc(sizeof(char *) * (count + 2));
	if (!new_tab)
		return (NULL);
	while (old && old[i] && i < count)
	{
		new_tab[i] = old[i];
		i++;
	}
	new_tab[i] = new_str;
	new_tab[i + 1] = NULL;
	if (old)
		free(old);
	return (new_tab);
}
