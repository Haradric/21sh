/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 19:37:22 by mbraslav          #+#    #+#             */
/*   Updated: 2017/09/04 19:37:23 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	process_string(t_list *list, t_prg *prg, t_list **arg)
{
	t_token	*token;
	t_list	*elem;

	token = list->content;
	if (ft_strstr(token->content, ">&"))
		redir(token, prg);
	else
	{
		if (!(elem = ft_lstnew(NULL, 0)))
		{
			ft_perror("21sh:", "");
			return (0);
		}
		ft_lstpushback(arg, elem);
		elem->content = ft_strdup(token->content);
	}
	return (1);
}

static int	get_fd(char *file, int mode)
{
	int		fd;

	fd = open(file, mode, 0644);
	if (fd < 0)
		ft_perror("21sh:", file);
	return (fd);
}

static int	process_redir(t_list *list, t_prg *prg)
{
	t_token *current;
	t_token	*next;
	int		fd;

	current = list->content;
	if (!list->next || (next = list->next->content)->type != STRING)
		error("21sh: expected argument after redirection", "");
	if (!list->next || (next = list->next->content)->type != STRING)
		return (0);
	fd = 0;
	if (prg->out == 1 && current->op == REDIR_R)
		fd = get_fd(next->content, O_WRONLY | O_CREAT | O_TRUNC);
	else if (prg->out == 1 && current->op == REDIR2_R)
		fd = get_fd(next->content, O_WRONLY | O_CREAT | O_APPEND);
	else if (prg->in == 0 && current->op == REDIR_L)
		fd = get_fd(next->content, O_RDONLY);
	else if (prg->in == 0 && current->op == REDIR2_L)
		fd = heredoc(next->content);
	if (fd < 0)
		return (0);
	if (current->op == REDIR_R || current->op == REDIR2_R)
		prg->out = (fd) ? fd : prg->out;
	else
		prg->in = (fd) ? fd : prg->in;
	return (1);
}

static int	process_params(t_list *list, t_prg *prg, t_list **arg)
{
	int		status;
	t_token	*token;

	while (list)
	{
		status = 0;
		token = list->content;
		if (token->type == STRING)
			status = process_string(list, prg, arg);
		else if (token->op == REDIR_R || token->op == REDIR2_R || \
				token->op == REDIR_L || token->op == REDIR2_L)
		{
			status = process_redir(list, prg);
			list = list->next;
		}
		else
			break ;
		if (!status)
			return (0);
		list = list->next;
	}
	return (1);
}

t_prg		*get_program(t_list *list)
{
	t_prg	*prg;
	t_list	*arg;

	if (!list || !(prg = ft_memalloc(sizeof(t_prg))))
		return (NULL);
	arg = NULL;
	prg->out = 1;
	arg = ft_lstnew(NULL, 0);
	arg->content = get_prg_name(list);
	if (((t_token *)list->content)->type == STRING)
		list = list->next;
	if (!process_params(list, prg, &arg))
	{
		free_prg(prg);
		ft_lstfreelist(&arg, free);
		return (NULL);
	}
	prg->argv = arg_list_to_arr(arg);
	prg->path = get_path(prg->argv[0]);
	ft_lstfreelist(&arg, free);
	return (prg);
}
