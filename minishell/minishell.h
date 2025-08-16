/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:01:24 by clfouger          #+#    #+#             */
/*   Updated: 2025/08/16 10:44:20 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>

# define SUCCESS 0
# define FAILURE 1

// STRUCTURES

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

// FONCTIONS

#endif