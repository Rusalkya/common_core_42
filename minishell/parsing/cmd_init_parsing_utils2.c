/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init_parsing_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 17:25:02 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*create_and_parse_cmd(char *part, t_hub *hub)
{
	t_cmd	*curr;

	curr = malloc(sizeof(t_cmd));
	if (!curr)
		return (NULL);
	ft_memset(curr, 0, sizeof(t_cmd));
	curr->next = NULL;
	parse_command(part, curr, hub);
	return (curr);
}

static void	link_commands(t_cmd **head, t_cmd **prev, t_cmd *curr)
{
	if (!*head)
		*head = curr;
	if (*prev)
		(*prev)->next = curr;
	*prev = curr;
}

t_cmd	*parse_pipeline(const char *input, t_hub *hub)
{
	char	**parts;
	t_cmd	*head;
	t_cmd	*prev;
	t_cmd	*curr;
	int		i;

	if (!input || !validate_buffer_syntax((char *)input))
	{
		hub->last_value = 2;
		return (NULL);
	}
	head = NULL;
	prev = NULL;
	i = -1;
	parts = split_pipeline_quotes(input);
	if (!parts)
		return (NULL);
	while (parts[++i])
	{
		curr = create_and_parse_cmd(parts[i], hub);
		if (!curr)
			break ;
		link_commands(&head, &prev, curr);
	}
	return (free_str_tab(parts), head);
}

void	handle_pipe_extraction(const char *input, char **result,
		int *vars, int *start)
{
	result[vars[1]] = ft_substr(input, *start, vars[0] - *start);
	vars[1]++;
	vars[0]++;
	while (input[vars[0]] && (input[vars[0]] == ' ' || input[vars[0]] == '\t'))
		vars[0]++;
	*start = vars[0];
}
