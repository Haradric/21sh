/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:35:16 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/06 15:35:17 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**g_env;
int		g_isparent;

int		main(int argc, char **argv, char **environ)
{
	g_isparent = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	env_init(environ);
	if (argc == 1)
		return (shell_interactive());
	else
		return (shell_noninteractive(argc, argv));
}
