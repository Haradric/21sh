/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:57:40 by mbraslav          #+#    #+#             */
/*   Updated: 2017/09/05 13:57:41 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char	**g_env;

void		run_pipeline(t_list *pipeline)
{
	t_list	*elem;
	t_prg	*prg;
	pid_t	pid;

	elem = pipeline;
	while (elem)
	{
		prg = elem->content;
		pid = fork();
		if (pid == -1)
		{
			ft_perror("21sh:", "fork:");
			break ;
		}
		else if (pid == 0)
			run_process(pipeline, prg);
		elem = elem->next;
	}
	close_fds(pipeline, NULL);
	while ((pid = wait(NULL)) > 0)
		;
	if (errno != ECHILD)
		ft_perror("21sh:", "wait:");
}

void		run_command(t_list *list)
{
	t_list	*pipeline;
	t_prg	*prg;

	get_pipeline(list);
	while ((pipeline = get_pipeline(NULL)))
	{
		prg = pipeline->content;
		if (ft_lstlen(pipeline) == 1 && \
			(!ft_strcmp(prg->argv[0], "cd") || \
			!ft_strcmp(prg->argv[0], "setenv") || \
			!ft_strcmp(prg->argv[0], "unsetenv") || \
			!ft_strcmp(prg->argv[0], "exit")))
			run_builtin(prg->argv);
		else
			run_pipeline(pipeline);
		ft_lstfreelist(&pipeline, free_prg);
	}
}
