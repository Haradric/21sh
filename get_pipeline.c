/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 16:54:41 by mbraslav          #+#    #+#             */
/*   Updated: 2017/09/01 16:54:42 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		connect_with_pipe(t_prg *input, t_prg *output)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_perror("21sh:", "pipe:");
		return (0);
	}
	if (input->out > 2)
		close(input->out);
	input->out = fd[1];
	if (output->in > 2)
		close(output->in);
	output->in = fd[0];
	return (1);
}

static int		add_prg_to_list(t_token *prev, t_list *list, t_list **pipeline)
{
	t_prg			*prg;
	t_list			*elem;

	if (!(prg = get_program(list)))
		return (0);
	ft_lstpushback(pipeline, elem = ft_lstnew(NULL, 0));
	elem->content = prg;
	if (prev && prev->op == PIPE)
		if (!connect_with_pipe(elem->prev->content, prg))
			return (0);
	return (1);
}

static t_list	*find_last_elem(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = list->content;
		if (token->op == PIPE)
			return (list->next);
		if (token->op == SEMICOLON)
		{
			while (list->next && (token = list->next->content)->op == SEMICOLON)
				list = list->next;
			return (list->next);
		}
		list = list->next;
	}
	return (NULL);
}

t_list			*get_pipeline(t_list *token_list)
{
	static t_list	*list = NULL;
	t_list			*pipeline;
	t_token			*prev;

	if (token_list)
	{
		list = token_list;
		return (NULL);
	}
	pipeline = NULL;
	while (list)
	{
		prev = (list->prev) ? list->prev->content : NULL;
		if (prev && prev->op == SEMICOLON && pipeline)
			break ;
		if (!add_prg_to_list(prev, list, &pipeline))
		{
			ft_lstfreelist(&pipeline, free_prg);
			return (NULL);
		}
		list = find_last_elem(list);
	}
	return (pipeline);
}
