/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:44:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/15 12:25:16 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_history(char *input)
{
	if (input && *input)
		add_to_history(input);
}

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		printf("exit\n");
		exit(0);
	}
	add_to_history(input);
	return (input);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = read_input();
		printf("Commande : %s\n", line);
		free(line);
	}
	return (0);
}
