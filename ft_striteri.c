/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:25:46 by clfouger          #+#    #+#             */
/*   Updated: 2025/04/30 12:19:33 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	to_upper_each(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "hello world!";

	ft_striteri(str, to_upper_each);
	printf("%s\n", str);
	return (0);
}
*/
