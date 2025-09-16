/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 15:51:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_error = 0;

t_info	*create_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error("malloc info", NULL), NULL);
	info->env = NULL;
	info->exp = NULL;
	return (info);
}

void	display_prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			// TODO: Parse input and execute commands
			printf("Command: %s\n", input);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = create_info();
	if (!info)
		return (1);
	ft_creat_env(info, env);
	if (g_error == 1)
		return (1);
	
	// Setup signal handling here
	
	display_prompt();
	
	// Cleanup resources
	// TODO: Free all allocated memory
	
	return (g_error);
}
