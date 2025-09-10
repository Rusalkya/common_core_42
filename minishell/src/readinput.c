/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:44:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/16 14:49:56 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	buffer[1024];

	while (1)
	{
		printf("minishell$ ");
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
			break ;
		buffer[strcspn(buffer, "\n")] = '\0';
		printf("Commande : %s\n", buffer);
	}
	return (0);
}
