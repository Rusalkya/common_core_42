/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/09/11 15:10:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
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
# include <stdbool.h>

# define SUCCESS 0
# define FAILURE 1

extern int	g_error;

// TOKEN STRUCTURES
typedef struct s_token
{
	char				*str;
	char				*str_backup; //pour debug et heredoc
	bool				var_exists; //pour les var d'environnement 
	int					type;
	int					status; //quotes
	bool				join; //true si on associe ce token au suivant
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

// I/O REDIRECTION STRUCTURES
typedef struct s_io_fds
{
	char				*infile; // <
	char				*outfile; // >> et >
	char				*heredoc_delimiter; //delimiterur pour <<
	bool				heredoc_quotes; //true si le heredoc est entre "x"
	int					fd_in;
	int					fd_out;
	int					stdin_backup; //restaure l'entree du terminal apre une exec
	int					stdout_backup; //restaure l'entree du terminal apre une exec
}						t_io_fds;

// COMMAND STRUCTURES
typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

// CARLOS STRUCTURES
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

// ENUMERATIONS
enum					e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum					e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

// PARSING FUNCTIONS
t_token	*lst_new_token(char *value, int type);
void	lst_add_back_token(t_token **lst, t_token *new_tok);
void	lstclear_token(t_token **lst, void (*del)(void *));

// BUILTINS FUNCTIONS
void	ft_cd(t_cmd *cd, t_info *info);
void	ft_echo(t_cmd *echo);
char	*ft_pwd(void);
void	ft_env(t_info *info);

// ENV FUNCTIONS
void	ft_creat_env(t_info *info, char **envp);
void	ft_update_env(char *var, char *value, t_info *info);
void	ft_add_env(char *src, t_info *info);

// EXPORT FUNCTIONS
int		ft_strcmp_equal(char *s1, char *s2);
int		does_it_exist(char *src, t_info *info);
void	ft_creat_export(t_info *info, char **envp);
void	ft_sort_export(t_info *info);
void	ft_export(t_cmd *export, t_info *info);
void	ft_add_export(char *src, t_info *info);
void	ft_update_export(char *var, char *value, t_info *info);

// ERROR FUNCTIONS
void	ft_error(const char *str, const char *error);

#endif
