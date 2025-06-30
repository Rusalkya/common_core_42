/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:22:41 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/27 15:28:37 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static char	**convert_argv(int argc, char *argv[], char **split);

char	**get_args_split(int argc, char *argv[])
{
	char	**split;

	if (argc < 2)
		return (NULL);
	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		if ((!split) || (!split[0]))
		{
			free (split);
			return (NULL);
		}
		return (split);
	}
	split = malloc (sizeof (char *) * argc);
	if (!split)
		return (NULL);
	return (convert_argv(argc, argv, split));
}

static char	**convert_argv(int argc, char *argv[], char **split)
{
	int		i;
	int		j;

	i = 0;
	while (i < argc - 1)
	{
		split[i] = ft_strdup(argv[i + 1]);
		if (!split[i])
		{
			j = 0;
			while (j < i)
				free (split[j++]);
			free (split);
			return (NULL);
		}
			i++;
	}
	split[i] = NULL;
	return (split);
}

void	parse_args_to_stack(char **args, t_node **a)
{
	int		value;
	int		i;

	i = 0;
	while (args[i])
	{
		if (!is_valid_int(args[i]))
		{
			ft_putstr_fd("Error\n", 2);
			free_split(args);
			free_stack(a);
			exit(1);
		}
		value = ft_atoi_safer(args[i]);
		append_node(a, create_node(value));
		i++;
	}
}

void	free_split(char **split)
{
	int		i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
