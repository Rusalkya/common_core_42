/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_n_quotes_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 15:48:05 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef struct s_expansion_vars
{
	int		i;
	int		j;
	int		quote_state;
}	t_expansion_vars;

typedef struct s_process_data
{
	char			*buffer;
	int				*i;
	int				quote_state;
	char			*result;
	int				*j;
	t_hub			*hub;
}	t_process_data;

static void	copy_var_value(char *var_value, char *result, int *j)
{
	int	k;

	if (var_value)
	{
		k = 0;
		while (var_value[k])
			result[(*j)++] = var_value[k++];
		free(var_value);
	}
}

static int	process_dollar_in_quotes(t_process_data *data)
{
	char	*var_value;

	if (data->buffer[*data->i] == '$' && data->quote_state != 1)
	{
		var_value = process_special_var(data->buffer, data->i, data->hub);
		if (!var_value && data->buffer[*data->i + 1]
			&& (ft_isalnum(data->buffer[*data->i + 1])
				|| data->buffer[*data->i + 1] == '_'))
			var_value = process_regular_var(data->buffer, data->i, data->hub);
		else if (!var_value)
		{
			if (data->buffer[*data->i + 1] == '"'
				|| data->buffer[*data->i + 1] == '\'')
				(*data->i)++;
			else
				data->result[(*data->j)++] = data->buffer[(*data->i)++];
			return (1);
		}
		copy_var_value(var_value, data->result, data->j);
		return (1);
	}
	return (0);
}

static char	*process_buffer_expansion(char *buffer, t_hub *hub)
{
	char				*result;
	t_process_data		data;
	t_expansion_vars	vars;

	result = malloc(ft_strlen(buffer) * 4 + 1024);
	if (!result)
		return (NULL);
	vars = (t_expansion_vars){0, 0, 0};
	data = (t_process_data){buffer, &vars.i, vars.quote_state,
		result, &vars.j, hub};
	while (buffer[vars.i])
	{
		data.quote_state = handle_quotes(buffer[vars.i], vars.quote_state);
		vars.quote_state = data.quote_state;
		if (!process_dollar_in_quotes(&data))
			result[vars.j++] = buffer[vars.i++];
	}
	result[vars.j] = '\0';
	result = realloc(result, vars.j + 1);
	return (result);
}

char	*expand_vars_with_quotes(char *buffer, t_hub *hub)
{
	char	*result;

	if (!buffer)
		return (NULL);
	result = process_buffer_expansion(buffer, hub);
	return (result);
}
