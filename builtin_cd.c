/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 17:17:54 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/27 17:17:55 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	change_dir(const char *path)
{
	if (access(path, F_OK))
	{
		error("cd: no such file or directory:", path);
		return (0);
	}
	if (!is_dir(path))
	{
		error("cd: not a directory:", path);
		return (0);
	}
	if (chdir(path))
	{
		error("chdir():", "an error occured");
		return (0);
	}
	return (1);
}

static void	minishell_cd(char *dir)
{
	char	buff[BUFF_SIZE];
	char	*pwd;

	ft_memset(buff, 0, BUFF_SIZE);
	if (!ft_strcmp(dir, "-"))
		pwd = ft_strdup(get_env_var("OLDPWD"));
	else if (!ft_strncmp(dir, "~/", 2))
	{
		minishell_cd(get_env_var("HOME"));
		pwd = ft_strdup(dir + 2);
	}
	else
		pwd = ft_strdup(dir);
	getcwd(buff, BUFF_SIZE);
	if (ft_strcmp(pwd, "") && !change_dir(pwd))
	{
		free(pwd);
		return ;
	}
	minishell_setenv("OLDPWD", buff);
	getcwd(buff, BUFF_SIZE);
	minishell_setenv("PWD", buff);
	if (!ft_strcmp(dir, "-"))
		ft_printf("%s\n", buff);
	free(pwd);
}

void		builtin_cd(int argc, char **argv)
{
	if (argc == 1)
		minishell_cd(get_env_var("HOME"));
	else if (argc == 2)
		minishell_cd(argv[1]);
	else
		write(2, "cd: too many arguments\n", 23);
}
