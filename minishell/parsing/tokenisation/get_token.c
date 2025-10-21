/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:49:35 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 14:22:00 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	validate_token_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next || current->next->type == PIPE)
				return (false);
		}
		if (current->type >= INPUT && current->type <= APPEND)
		{
			if (!current->next || current->next->type != WORD)
				return (false);
			if (current->next && current->next->next
				&& current->next->next->type >= INPUT
				&& current->next->next->type <= APPEND)
				return (false);
		}
		if (current->type == ERROR_TOKEN)
			return (false);
		current = current->next;
	}
	return (true);
}

char	**split_tokens_lexer(const char *str, t_hub *hub)
{
	char	**result;
	int		i;
	int		count;
	char	*token;

	result = NULL;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			i++;
			continue ;
		}
		if (is_operator_char(str[i]))
			token = extract_operator(str, &i, hub);
		else
			token = extract_word(str, &i, hub);
		result = realloc_tab(result, token, ++count, hub);
	}
	return (result);
}

int	get_token_type(char *str)
{
	if (!str)
		return (END);
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	if (ft_strcmp(str, "<") == 0)
		return (INPUT);
	if (ft_strcmp(str, ">") == 0)
		return (TRUNC);
	if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	if (ft_strnstr(str, "||", ft_strlen(str)) || ft_strnstr(str, "<<<",
			ft_strlen(str)) || ft_strnstr(str, ">>>", ft_strlen(str))
		|| ft_strnstr(str, "><", ft_strlen(str)) || ft_strnstr(str, "<>",
			ft_strlen(str)))
		return (ERROR_TOKEN);
	return (WORD);
}

void	split_tokens(t_cmd *lst_cmd, char *str_cmd, t_hub *hub)
{
	char	**strs;
	t_token	*new_token;
	t_token	*temp;
	int		i;
	int		type;

	new_token = NULL;
	strs = split_tokens_lexer(str_cmd, hub);
	if (!strs || !strs[0])
		return ;
	lst_cmd->args = realloc_tab(lst_cmd->args, strs[0], 0, hub);
	i = 1;
	while (strs[i])
	{
		type = get_token_type(strs[i]);
		lst_add_back_token(&new_token, lst_new_token(ft_strdup(strs[i]), type,
				hub));
		i++;
	}
	lst_add_back_token(&new_token, lst_new_token(NULL, END, hub));
	temp = new_token;
	free_str_tab(strs);
}

int	check_redirections(char *buffer, int *i)
{
	if (!buffer[*i])
		return (1);
	if (!check_redir_syntax(buffer, i))
		return (0);
	if (!check_pipe_syntax(buffer, i))
		return (0);
	return (1);
}
