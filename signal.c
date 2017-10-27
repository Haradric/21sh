/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 15:44:57 by mbraslav          #+#    #+#             */
/*   Updated: 2017/08/29 15:44:58 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "input.h"

extern int		g_isparent;
extern t_term	*g_term;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (g_isparent == 0)
			exit(0);
	}
	else if (signal == SIGQUIT)
		exit(0);
}

void	signal_handler_input(int signal)
{
	if (signal == SIGINT)
	{
		ft_memset(g_term->entry->content, 0, ft_strlen(g_term->entry->content));
		g_term->cursor = g_term->entry->content;
		write(0, "\n", 1);
		ft_putstr(get_env_var("PROMPT"));
	}
	if (signal == SIGQUIT)
		exit(0);
}
