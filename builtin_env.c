/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:53:37 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:53:39 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char	**g_env;

void	builtin_env(int argc, char **argv)
{
	int		i;

	if (argc == 1 || argv[1] == 0)
	{
		i = 0;
		while (g_env[i])
			ft_printf("%s\n", g_env[i++]);
	}
}
