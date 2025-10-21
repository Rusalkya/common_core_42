/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:41:04 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/17 10:28:55 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_minishell(t_rl *shell)
{
	shell->input = NULL;
	shell->prompt = "rl$ ";
	shell->exit_status = 0;
	shell->gc = NULL;
}

void	free_sh_input(t_rl *sh)
{
	free(sh->input);
	sh->input = NULL;
}

char	*read_input(t_hub *hub)
{
	int		len;
	t_rl	*sh;

	sh = hub->rl;
	if (sh->input)
		free_sh_input(sh);
	if (isatty(STDIN_FILENO))
		sh->input = readline(sh->prompt);
	else
		sh->input = get_next_line(STDIN_FILENO);
	if (!sh->input)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		cleanup_shell(sh);
		exit(hub->last_value);
	}
	len = ft_strlen(sh->input);
	if (!isatty(STDIN_FILENO) && len > 0 && sh->input[len - 1] == '\n')
		sh->input[len - 1] = '\0';
	if (isatty(STDIN_FILENO))
		add_to_history(sh->input);
	return (sh->input);
}

static void	print_str_tab(char **tab, char *label)
{
	int	i;

	printf("%s: ", label);
	i = 0;
	while (tab && tab[i])
	{
		printf("[%s] ", tab[i]);
		i++;
	}
	printf("\n");
}

void	print_parsed_commands(t_cmd *cmds)
{
	t_out	*out;
	int		n;

	n = 1;
	while (cmds)
	{
		printf("Command %d: ", n);
		if (cmds->args && cmds->args[0])
			printf("%s\n", cmds->args[0]);
		else
			printf("(null)\n");
		print_str_tab(cmds->args, "Args");
		print_str_tab(cmds->file_in, "File_in");
		printf("File_out: ");
		out = cmds->file_out;
		while (out)
		{
			printf("[%s] (type:%d) ", out->file, out->type);
			out = out->next;
		}
		printf("\n---\n");
		cmds = cmds->next;
		n++;
	}
}
