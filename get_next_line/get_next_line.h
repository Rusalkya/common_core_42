/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:37:26 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/20 10:25:39 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*getl(char *sbuffer);
char	*get_rest(char *sbuffer);
char	*gnl_error(char **sbuffer, char *temp);
char	*gnl_free(char **sbuffer);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char const *s2);

#endif