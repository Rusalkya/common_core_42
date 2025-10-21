/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/09 15:35:29 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token)
{
	t_token	*token_swap;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		if (token->str)
			free(token->str);
		if (token->str_backup)
			free(token->str_backup);
		token_swap = token;
		token = token->next;
		free(token_swap);
	}
}

void	free_rl(t_rl *rl)
{
	if (rl == NULL)
		return ;
	if (rl->input)
		free(rl->input);
	free(rl);
}
