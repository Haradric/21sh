/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:53:45 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:53:46 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char	**g_env;

void	minishell_setenv(const char *var, const char *value)
{
	char	*new;
	size_t	len;
	int		i;

	if (get_env_var(var) == NULL)
		add_env_var(var, value);
	else
	{
		i = 0;
		len = ft_strlen(var);
		while (ft_strncmp(g_env[i], var, len))
			i++;
		new = ft_strnew(len + ft_strlen(value) + 1);
		ft_strcat(ft_strcat(ft_strcpy(new, var), "="), value);
		free(g_env[i]);
		g_env[i] = new;
	}
}

void	builtin_setenv(int argc, char **argv)
{
	if (argc == 2)
		minishell_setenv(argv[1], "");
	else if (argc == 3)
		minishell_setenv(argv[1], argv[2]);
	else
		write(2, "usage: setenv var [value]\n", 26);
}
