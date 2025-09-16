/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:49:35 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 15:50:22 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **split_tokens_lexer(const char *str)
{
    char **result = NULL;
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (str[i] == ' ')
        {
            i++;
            continue;
        }
        char *token;
        if (is_operator_char(str[i]))
            token = extract_operator(str, &i);
        else
            token = extract_word(str, &i);
        result = realloc_tab(result, token, ++count); // <== fonction utilitaire
    }
    return (result);
}

int get_token_type(char *str)
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
    return (WORD);
}

void split_tokens(t_command *lst_cmd, char *str_cmd)
{
    char    **strs;
    t_token *new_token = NULL;
    t_token *temp;
    int     i;

    strs = split_tokens_lexer(str_cmd);
    if (!strs || !strs[0])
        return ;
    lst_cmd->command = ft_strdup(strs[0]);
    i = 1;
    while (strs[i])
    {
        int type = get_token_type(strs[i]);
        lst_add_back_token(&new_token,
            lst_new_token(ft_strdup(strs[i]), type));
        i++;
    }
    lst_add_back_token(&new_token, lst_new_token(NULL, END));
    fill_args(&new_token, lst_cmd);
    temp = new_token;
    lstclear_token(&temp, &free);
    free_str_tab(strs);
}
