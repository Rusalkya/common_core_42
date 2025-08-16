/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:01:50 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/16 10:07:04 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lst_new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
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
		if (tmp->value)
			del(tmp->value);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
