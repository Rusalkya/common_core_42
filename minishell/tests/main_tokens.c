/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:52:07 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 15:52:41 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    t_command cmd;

    char *input = "echo \"hello world\" | grep hi > out.txt";

    printf("INPUT: %s\n\n", input);
    split_tokens(&cmd, input);

    printf("Command: %s\n", cmd.command);

    if (cmd.args)
    {
        int i = 0;
        while (cmd.args[i])
        {
            printf("Arg[%d]: %s\n", i, cmd.args[i]);
            i++;
        }
    }
    else
        printf("No args found.\n");

    return (0);
}
