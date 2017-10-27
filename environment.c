/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:05:25 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/26 17:05:26 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern char **g_env;

void	env_init(char **environ)
{
	char	*tmp;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	if ((g_env = ft_memalloc(sizeof(char *) * (i + 1))) == NULL)
		ft_perror("21sh:", "can't allocate memory for storing environment:");
	while (--i >= 0)
		g_env[i] = ft_strdup(environ[i]);
	minishell_setenv("SHELL", "minishell");
	tmp = get_env_var("USER");
	tmp = ft_strjoin((tmp) ? tmp : "$", "> ");
	minishell_setenv("PROMPT", tmp);
	free(tmp);
}

char	*get_env_var(const char *var)
{
	size_t	len;
	int		i;

	if (!var || !(len = ft_strlen(var)))
		return (NULL);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], var, len))
			break ;
		i++;
	}
	if (!g_env[i])
		return (NULL);
	else
		return (g_env[i] + len + 1);
}

void	add_env_var(const char *var, const char *value)
{
	char	**new_env;
	char	*new_var;
	size_t	len;
	int		i;

	len = ft_strlen(var) + ft_strlen(value) + 1;
	new_var = ft_strnew(len);
	ft_strcat(ft_strcat(ft_strcpy(new_var, var), "="), value);
	i = 0;
	while (g_env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	new_env[i] = 0;
	new_env[i + 1] = 0;
	i = 0;
	while (g_env[i])
	{
		new_env[i] = (g_env)[i];
		i++;
	}
	new_env[i] = new_var;
	free(g_env);
	g_env = new_env;
}
