/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:09:12 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/06 12:33:00 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;

	if (!s[0])
		return (0);
	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_words++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		nb_words++;
	return (nb_words);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c); // Assure-toi que ft_split est bien déclarée

void	print_split(char **split)
{
	int	i = 0;
	if (!split)
	{
		printf("NULL returned\n");
		return;
	}
	while (split[i])
	{
		printf("split[%d] = \"%s\"\n", i, split[i]);
		i++;
	}
	// libère la mémoire après test
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
/*
#include <stdio.h>

int	main(void)
{
	char **res;

	printf("Test 1 : \"hello world\"\n");
	res = ft_split("hello world", ' ');
	print_split(res);

	printf("\nTest 2 : \"--a--b---c---\"\n");
	res = ft_split("--a--b---c---", '-');
	print_split(res);

	printf("\nTest 3 : \"\"\n");
	res = ft_split("", ' ');
	print_split(res);

	printf("\nTest 4 : \"     spaced words here     \"\n");
	res = ft_split("     spaced words here     ", ' ');
	print_split(res);

	printf("\nTest 5 : \"no_separator\"\n");
	res = ft_split("no_separator", ',');
	print_split(res);

	return (0);
}
*/