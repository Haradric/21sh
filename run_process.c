/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 16:07:46 by mbraslav          #+#    #+#             */
/*   Updated: 2017/09/01 16:07:47 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_isparent;
extern char	**g_env;

static void	manage_fds(t_prg *prg)
{
	if (prg->in != 0)
		if (dup2(prg->in, 0) == -1)
			ft_perror("21sh:", "");
	if (prg->out != 1)
		if (dup2(prg->out, 1) == -1)
			ft_perror("21sh:", "");
	if (prg->r_in && prg->r_out)
		if (dup2(prg->r_out, prg->r_in) == -1)
			ft_perror("21sh:", "");
}

void		run_process(t_list *pipeline, t_prg *prg)
{
	g_isparent = 0;
	close_fds(pipeline, prg);
	manage_fds(prg);
	if (!ft_strcmp(prg->argv[0], "cd") || \
		!ft_strcmp(prg->argv[0], "echo") || \
		!ft_strcmp(prg->argv[0], "env") || \
		!ft_strcmp(prg->argv[0], "setenv") || \
		!ft_strcmp(prg->argv[0], "unsetenv") || \
		!ft_strcmp(prg->argv[0], "exit"))
	{
		run_builtin(prg->argv);
		exit(0);
	}
	else if (!ft_strncmp(prg->argv[0], "~/", 2) || \
			ft_strstr(prg->argv[0], "./"))
		run_executable(prg);
	else if (prg->path && !access(prg->path, F_OK))
		execve(prg->path, prg->argv, g_env);
	else
		error("21sh: command not found:", prg->argv[0]);
	exit(1);
}

void		close_fds(t_list *pipeline, t_prg *exc)
{
	t_prg	*prg;

	while (pipeline)
	{
		prg = pipeline->content;
		if ((!exc && prg->in != 0) || (exc && exc->in != prg->in))
			if (close(prg->in) == -1)
				ft_perror("21sh:", ft_itoa(prg->in));
		if ((!exc && prg->out != 1) || (exc && exc->out != prg->out))
			if (close(prg->out) == -1)
				ft_perror("21sh:", ft_itoa(prg->out));
		if (exc && exc->r_in != prg->r_in && prg->r_in > 2)
			if (close(prg->r_in) == -1)
				ft_perror("21sh:", ft_itoa(prg->r_in));
		if (exc && exc->r_out != prg->r_out && prg->r_out > 2)
			if (close(prg->r_out) == -1)
				ft_perror("21sh:", ft_itoa(prg->r_out));
		pipeline = pipeline->next;
	}
}

void		run_builtin(char **argv)
{
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (!ft_strcmp(argv[0], "cd"))
		builtin_cd(argc, argv);
	else if (!ft_strcmp(argv[0], "echo"))
		builtin_echo(argc, argv);
	else if (!ft_strcmp(argv[0], "env"))
		builtin_env(argc, argv);
	else if (!ft_strcmp(argv[0], "setenv"))
		builtin_setenv(argc, argv);
	else if (!ft_strcmp(argv[0], "unsetenv"))
		builtin_unsetenv(argc, argv);
	else if (!ft_strcmp(argv[0], "exit"))
		builtin_exit(argc, argv);
}

void		run_executable(t_prg *prg)
{
	if (access(prg->path, F_OK) == -1)
	{
		ft_perror("21sh:", prg->argv[0]);
		exit(1);
	}
	else
		execve(prg->path, prg->argv, g_env);
}
