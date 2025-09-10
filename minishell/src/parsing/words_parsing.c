/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 09:38:19 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/16 10:37:31 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	split_tokens(t_command lst_cmd, char *str_cmd)
{
	t_token *new_token;
	t_token *temp;
	char **strs;
	int i;

	new_token = (NULL);
	strs = ft_split(str_cmd, ' ');
	if (!strs)
		return ;
	lst_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_token = lst_new_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	temp = new_token;
	i = 1;
	while (strs[i++])
		lst_add_back_token(&new_token, lst_new_token(ft_strdup(strs[i]), NULL,
				WORD, DEFAULT));
	lst_add_back_token(&new_token, lst_new_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_token, last_cmd);
	lstclear_token(&temp, &free_ptr);
	free_str_tab(strs);
}