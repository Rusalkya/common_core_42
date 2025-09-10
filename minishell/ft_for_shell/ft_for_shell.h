/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:02:02 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:05:58 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FOR_SHELL_H

# define FT_FOR_SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include "libft/libft.h"

extern int	g_error;

typedef struct command_list
{
	int		fd;
	char	option;
	char	**src;
}				t_cmd;

typedef struct info_minishell
{
	char	**env;
	char	**exp;
}				t_info;

void	ft_cd(t_cmd *cd, t_info *info);
void	ft_echo(t_cmd *echo);
char	*ft_pwd(void);

// error

void	ft_error(const char *str, const char *error);

// export

int		ft_strcmp_equal(char *s1, char *s2);
int		does_it_exist(char *src, t_info *info);
void	ft_creat_export(t_info *info, char **envp);
void	ft_sort_export(t_info *info);

// env

void	ft_creat_env(t_info *info, char **envp);
void	ft_update_env(char *new, t_info *info);

#endif