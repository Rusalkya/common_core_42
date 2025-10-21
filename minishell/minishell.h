/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:18:10 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 17:06:11 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define DEFAULT 0

extern volatile sig_atomic_t	g_sig;

// quotes
typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}								t_quote_type;

// token
typedef struct s_token
{
	char						*str;
	char						*str_backup;
	bool						var_exists;
	int							type;
	int							status;
	bool						join;
	struct s_token				*prev;
	struct s_token				*next;
	t_quote_type				quote;
}								t_token;

typedef struct info_minishell
{
	char						**env;
	char						**exp;
}								t_info;

// GARBAGE COLLECTOR

typedef struct s_gc_node
{
	void						*ptr;
	struct s_gc_node			*next;
}								t_gc;

// POUR READLINE

typedef struct s_rl
{
	char						*input;
	char						*prompt;
	int							exit_status;
	t_gc						*gc;
}								t_rl;

// POUR LES COMMANDES

typedef struct s_files_out
{
	int							type;
	char						*file;
	struct s_files_out			*next;
}								t_out;

typedef struct s_command
{
	int							i;
	int							std_in;
	char						**args;
	int							fd_in;
	int							fd_out;
	char						**file_in;
	t_out						*file_out;
	char						**heredoc;
	int							i_hd;
	struct s_command			*next;
}								t_cmd;

// POUR LES ENFANTS

typedef struct s_pipeline
{
	char						**paths;
	char						*path_name;
	pid_t						*lst_pid;
	int							error;
	int							**fd;
	int							nb_fd;
	int							i_fd;
	int							i_pd;
}								t_ppl;

// ENUMERATIONS

enum							e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	ERROR_TOKEN,
	END
};

typedef struct hub
{
	t_info						*info;
	t_cmd						*cmd;
	t_ppl						*ppl;
	t_gc						*gc;
	t_token						*token;
	t_rl						*rl;
	t_quote_type				*quote;
	int							last_value;
}								t_hub;

typedef struct s_expand
{
	char						*buffer;
	t_hub						*hub;
	t_gc						*gc;
	int							i;
	int							j;
	int							is_pid;
	char						*var;
	char						*value;
}								t_expand;

// BUILT-IN

int							ft_cd(t_hub *hub, t_cmd *cmd, t_info *info);
int							ft_echo(t_cmd *cmd);
int							ft_pwd(void);
void						ft_exit(t_hub *hub, int i);
int							ft_exit_bi(t_hub *hub);
int							ft_unset(t_hub *hub, t_info *info, t_cmd *cmd);
int							ft_built_in(t_hub *hub, t_info *info,
								t_cmd *cmd);
// export
int							ft_export(t_hub *hub, t_info *info, t_cmd *cmd);
void						ft_creat_export(t_hub *hub, t_info *info,
								char **envp);
void						ft_sort_export(t_info *info);
void						ft_add_export(t_hub *hub, t_info *info,
								char *new);
void						ft_update_export(t_hub *hub, t_info *info,
								char *new);
// env
int							ft_env(t_info *info, t_cmd *cmd);
void						ft_creat_env(t_hub *hub, t_info *info,
								char **envp);
void						ft_update_env(t_hub *hub, t_info *info,
								char *new);
void						ft_add_env(t_hub *hub, t_info *info, char *new);

// EXEC

int							files(t_cmd *cmd);
int							pipeline(t_hub *hub);
int							find_command(t_hub *hub, t_ppl *ppl,
								char **args);
int							heredoc(t_cmd *cmd, t_ppl *ppl);
void						sigint_hd(int sig);
int							ft_wait(t_hub *hub, t_ppl *ppl);
// utils
int							verif_built_in(char *arg);
void						exec_end(t_cmd *cmd, t_ppl *ppl);
void						pipe_error(t_ppl *ppl);
void						close_files(t_cmd *cmd);
void						pipeline_end(t_hub *hub, int error);
int							built_in(t_hub *hub, t_info *info, t_cmd *cmd);

// UTILS

// utils_1
void						remove_line_env(t_hub *hub, t_info *info,
								char *str);
int							does_it_exist_env(t_info *info, char *src);
char						*ft_getenv(t_hub *hub, t_info *info, char *str);
int							does_it_exist(t_info *info, char *src);
int							ft_strcmp_equal(char *s1, char *s2);
// utils_exec
int							setting_exec(t_hub *hub, t_cmd *cmd,
								t_ppl *ppl);
void						free_exec(t_hub *hub, t_ppl *ppl);
void						close_files(t_cmd *cmd);
// signal
void						sigint_prompt(int sig);
void						sig_inter(void);
void						signals_parent_wait(void);
void						signals_child(void);
void						signals_heredoc(void);
// builtins
int							find_egual(char *str);
int							its_empty(char *str);
void						export_condition(t_hub *hub, t_info *info,
								t_cmd *cmd, int i);

// READLINE
void						init_minishell(t_rl *shell);
void						add_to_history(char *input);
void						add_to_history_custom(char *input);
void						clear_current_line(void);
void						cleanup_shell(t_rl *shell);
char						*read_input(t_hub *hub);
void						handle_signal_interrupt(t_rl *shell);
int							main_shell_loop(t_rl *shell);

// EXEC (temporaire pour compilation en test)
void						execute_pipeline(t_hub *hub);
void						print_parsed_commands(t_cmd *commands);

// STRUCT

t_hub						*creat_hub(char **envp);
// void							creat_cmd(t_hub *hub);
void						creat_ppl(t_hub *hub);
void						creat_info(t_hub *hub);

// FREE

void						free_ppl(t_ppl *ppl);
void						free_info(t_info *info);
void						free_out(t_out *out);
void						free_cmd(t_cmd *cmd);
void						free_token(t_token *token);
void						free_rl(t_rl *rl);

// PARSING FONCTIONS

// parse_expand.c
char						*expand_vars(char *buffer, t_hub *hub);
int							expand_variables(t_expand *exp);
int							expand_special_vars(t_expand *exp);
int							expand_regular_var(t_expand *exp);
// parse_expand_utils.c
char						*get_var_value(char *var, t_hub *hub);
char						*replace_var(t_expand *exp);
int							handle_quotes(char c, int quote_state);
int							process_var(t_expand *exp);
int							is_valid_var_char(char c);
int							handle_var_expansion(t_expand *exp);
// parse_expand_quotes.c
char						*expand_vars_with_quotes(char *buffer,
								t_hub *hub);
// parse_expand_quotes_utils.c
char						*process_special_var(char *buffer, int *i,
								t_hub *hub);
char						*process_regular_var(char *buffer, int *i,
								t_hub *hub);
// cmd_init_parsing_utils.c
void						handle_quote_in_split(const char *input, int *i,
								char *quote);
int							count_pipeline_parts(const char *input);
void						extract_pipeline_parts(const char *input,
								char **result);
void						handle_pipe_extraction(const char *input,
								char **result, int *vars, int *start);
char						*find_command_in_tokens(char **tokens);
void						process_tokens(t_cmd *cmd, char **tokens);
void						skip_whitespace_in_parsing(char **tokens,
								int *i);
int							count_pipeline_commands(const char *input);
int							validate_buffer_syntax(char *buffer);
int							check_redir_syntax(char *buffer, int *i);
int							check_pipe_syntax(char *buffer, int *i);
// buffer_validation_utils.c
int							check_quoted_arg(char *buffer, int *j);
int							has_valid_filename(char *buffer, int start_pos);
void						advance_past_redirect(char *buffer, int *i);
int							skip_initial_spaces(char *buffer);
int							check_pipe_at_start(char *buffer);
int							process_buffer_char(char *buffer, int *i);
// split_args_utils.c
void						skip_whitespace(char *input, int *i);
char						*get_next_token(char *input, int *i,
								t_hub *hub);
void						move_until_word_end(const char *s, int *i);
// quote_utils.c
char						*remove_quotes(char *str);
int							check_quote_closure(char *buffer, int *i);

// quotes.c
char						*extract_quoted(const char *str, int *i,
								t_quote_type *quote_type);
char						*extract_unquoted(const char *str, int *i);
t_token						*create_token(char *str,
								t_quote_type quote_type, t_hub *hub);
t_token						*parse_tokens_with_quotes(const char *line,
								t_hub *hub);
// cmd_init_parsing.c
void						parse_redirections(char **tokens, t_cmd *cmd,
								t_hub *hub);
void						parse_command(char *input, t_cmd *cmd,
								t_hub *hub);
char						**split_pipeline_quotes(const char *input);
t_cmd						*parse_pipeline(const char *input, t_hub *hub);
// cmd_utils.c
void						parse_command_simplified(char *input,
								t_cmd *cmd, t_hub *hub);
// get_tokens.c
bool						validate_token_syntax(t_token *tokens);
char						**split_tokens_lexer(const char *str,
								t_hub *hub);
int							get_token_type(char *str);
void						split_tokens(t_cmd *lst_cmd, char *str_cmd,
								t_hub *hub);
bool						validate_token_syntax(t_token *tokens);
bool						validate_string_tokens(char **tokens, t_hub *hub);
// lst_parsing.c
t_token						*lst_new_token(char *value, int type,
								t_hub *hub);
void						lst_add_back_token(t_token **lst,
								t_token *new_tok);
void						lstclear_token(t_token **lst);
// split_args.c
bool						is_operator_char(char c);
char						*extract_operator(const char *str, int *i,
								t_hub *hub);
char						*extract_word(const char *str, int *i,
								t_hub *hub);
char						**realloc_tab(char **old, char *new_str,
								int count, t_hub *hub);
char						**realloc_tab_2(char **old, char *new_str,
								int count, t_hub *hub);
char						**enhanced_split_command(char *input,
								t_hub *hub);

// words_parsing.c
void						free_str_tab(char **strs);
void						fill_args(t_token **tokens, t_cmd *cmd,
								t_hub *hub);

// redirections.c
t_out						*create_output_redirect(char *filename,
								int type);
void						add_output_redirect(t_cmd *cmd, t_out *new_out);
int							handle_input_redirect(char **tokens, t_cmd *cmd,
								t_hub *hub, int *file_in_count);
int							handle_output_redirect(char **tokens,
								t_cmd *cmd, int type);
int							handle_heredoc_redirect(char **tokens,
								t_cmd *cmd, t_hub *hub);

// OTHER

void						ft_error(const char *str, const char *error);

#endif