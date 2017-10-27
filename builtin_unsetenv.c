/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:53:54 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:53:56 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char	**g_env;

static void	cp_env(char **old, char **new, const char *exeption)
{
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(exeption);
	while (old[i])
	{
		if (ft_strncmp(old[i], exeption, len))
		{
			new[j] = old[i];
			j++;
		}
		else
			free(old[i]);
		i++;
	}
}

void		minishell_unsetenv(const char *var)
{
	char	**new_env;
	int		i;

	if (!get_env_var(var))
		return ;
	i = 0;
	while (g_env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	new_env[i - 1] = 0;
	cp_env(g_env, new_env, var);
	free(g_env);
	g_env = new_env;
}

void		builtin_unsetenv(int argc, char **argv)
{
	if (argc == 2)
		minishell_unsetenv(argv[1]);
	else
		write(2, "usage: unsetenv var\n", 20);
}
