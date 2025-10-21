/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:42:20 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 12:32:59 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_pipeline_quotes(const char *input)
{
	char	**result;
	int		count;

	if (!input)
		return (NULL);
	count = count_pipeline_parts(input);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	extract_pipeline_parts(input, result);
	return (result);
}

typedef struct s_redirect_data
{
	char	**tokens;
	int		i;
	t_cmd	*cmd;
	t_hub	*hub;
	int		*file_in_count;
}	t_redirect_data;

static int	process_redirection_type(t_redirect_data *data)
{
	int	increment;

	increment = 1;
	if (ft_strcmp_equal(data->tokens[data->i], "<") == 0
		&& data->tokens[data->i + 1])
		increment = handle_input_redirect(&data->tokens[data->i], data->cmd,
				data->hub, data->file_in_count);
	else if (ft_strcmp_equal(data->tokens[data->i], ">") == 0
		&& data->tokens[data->i + 1])
		increment = handle_output_redirect(&data->tokens[data->i], data->cmd,
				0);
	else if (ft_strcmp_equal(data->tokens[data->i], ">>") == 0
		&& data->tokens[data->i + 1])
		increment = handle_output_redirect(&data->tokens[data->i], data->cmd,
				1);
	else if (ft_strcmp_equal(data->tokens[data->i], "<<") == 0
		&& data->tokens[data->i + 1])
		increment = handle_heredoc_redirect(&data->tokens[data->i], data->cmd,
				data->hub);
	return (increment);
}

void	parse_redirections(char **tokens, t_cmd *cmd, t_hub *hub)
{
	t_redirect_data	data;
	int				file_in_count;

	data.tokens = tokens;
	data.i = 0;
	data.cmd = cmd;
	data.hub = hub;
	data.file_in_count = &file_in_count;
	file_in_count = 0;
	while (tokens[data.i])
	{
		data.i += process_redirection_type(&data);
	}
}

void	parse_command(char *input, t_cmd *cmd, t_hub *hub)
{
	parse_command_simplified(input, cmd, hub);
}
