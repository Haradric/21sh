/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:45:36 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/06 15:45:38 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <term.h>
# include <errno.h>
# include "./libft/libft.h"

# define BUFF_SIZE 1024
# define READ_BUFF 16

typedef enum	e_toktype
{
	STRING = 1,
	OPERATOR
}				t_toktype;

typedef enum	e_op
{
	PIPE = 1,
	REDIR_L,
	REDIR_R,
	REDIR2_L,
	REDIR2_R,
	SEMICOLON
}				t_op;

typedef	struct	s_token
{
	t_toktype	type;
	char		*content;
	t_op		op;
}				t_token;

typedef struct	s_prg
{
	char		**argv;
	char		*path;
	int			in;
	int			out;
	int			r_in;
	int			r_out;
}				t_prg;

int				shell_interactive(void);
int				shell_noninteractive(int argc, char **argv);

void			env_init(char **environ);
char			*get_env_var(const char *var);
void			add_env_var(const char *var, const char *value);

char			*get_input(const char *prompt, t_list **hist);

t_list			*get_token_list(const char *str);
void			env_replace(t_list *elem);
void			quotes_remove(t_list *elem);

t_list			*get_pipeline(t_list *token_list);

t_prg			*get_program(t_list *list);
char			*get_prg_name(t_list *list);
char			*search_in_path(char *name);
char			*get_path(char *name);
void			redir(t_token *token, t_prg *prg);
char			**arg_list_to_arr(t_list *args);

void			run_builtin(char **argv);
void			run_executable(t_prg *prg);

void			run_process(t_list *pipeline, t_prg *prg);
void			run_command(t_list *toklist);
void			run_builtin(char **argv);
void			run_executable(t_prg *prg);
void			close_fds(t_list *pipeline, t_prg *exc);

int				heredoc(char *eol);

void			minishell_setenv(const char *var, const char *value);
void			minishell_unsetenv(const char *var);
void			builtin_cd(int argc, char **argv);
void			builtin_echo(int argc, char **argv);
void			builtin_env(int argc, char **argv);
void			builtin_setenv(int argc, char **argv);
void			builtin_unsetenv(int argc, char **argv);
void			builtin_exit(int argc, char **argv);

void			signal_handler(int signal);
void			signal_handler_input(int signal);

void			free_prg(void *prg);
void			free_token(void *token);
void			free_str_array(char **arr);

void			error(const char *error_msg, const char *str);
void			ft_perror(const char *error_msg, const char *str);
void			terminate(const char *error_msg, const char *str);

t_list			*str_to_list(char *str);
char			*list_to_str(t_list *list);
int				is_op(char c);
int				is_dir(const char *path);
int				is_empty(char *str);

#endif
