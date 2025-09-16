/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:01:50 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 12:07:59 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lst_new_token(char *value, int type)
{
	t_token	*token;

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

void	lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;
	t_token	*next;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->str)
			del(tmp->str);
		if (tmp->str_backup)
			del(tmp->str_backup);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
