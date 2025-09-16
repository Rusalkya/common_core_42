/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:24:21 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 15:49:32 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **realloc_tab(char **old, char *new_str, int count)
{
    char **new_tab;
    int i = 0;

    new_tab = malloc(sizeof(char *) * (count + 1));
    if (!new_tab)
        return (NULL);
    while (old && old[i])
    {
        new_tab[i] = old[i];
        i++;
    }
    new_tab[i++] = new_str;
    new_tab[i] = NULL;
    if (old)
        free(old);
    return (new_tab);
}

static bool is_operator_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static char *extract_word(const char *str, int *i)
{
    int start = *i;
    char quote = 0;
    char *word;

    while (str[*i])
    {
        if (!quote && (str[*i] == '\'' || str[*i] == '"'))
            quote = str[(*i)++];
        else if (quote && str[*i] == quote)
        {
            quote = 0;
            (*i)++;
        }
        else if (!quote && (str[*i] == ' ' || is_operator_char(str[*i])))
            break;
        else
            (*i)++;
    }
    word = ft_substr(str, start, *i - start);
    return (word);
}

static char *extract_operator(const char *str, int *i)
{
    int start = *i;

    if (str[*i] == '>' && str[*i + 1] == '>')
        *i += 2;
    else if (str[*i] == '<' && str[*i + 1] == '<')
        *i += 2;
    else
        (*i)++;
    return (ft_substr(str, start, *i - start));
}
