/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 19:36:41 by mbraslav          #+#    #+#             */
/*   Updated: 2017/09/04 19:36:42 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_prg_name(t_list *list)
{
	t_token	*token;

	token = list->content;
	if (token->type == STRING)
		return (ft_strdup(token->content));
	else
		return (ft_strdup("cat"));
}

char	*search_in_path(char *name)
{
	char	*path;
	char	buff[BUFF_SIZE];
	char	**path_list;
	int		i;

	path = NULL;
	i = 0;
	path_list = ft_strsplit(get_env_var("PATH"), ':');
	while (path_list && path_list[i])
	{
		ft_memset(buff, 0, 1024);
		ft_strcat(ft_strcat(ft_strcat(buff, path_list[i]), "/"), name);
		if (!access(buff, F_OK))
		{
			path = ft_strdup(buff);
			break ;
		}
		i++;
	}
	free_str_array(path_list);
	return (path);
}

char	*get_path(char *name)
{
	char	*path;

	if (!ft_strcmp(name, "cd") || \
		!ft_strcmp(name, "echo") || \
		!ft_strcmp(name, "env") || \
		!ft_strcmp(name, "setenv") || \
		!ft_strcmp(name, "unsetenv") || \
		!ft_strcmp(name, "exit"))
		path = NULL;
	else if (!ft_strncmp("~/", name, 2))
		path = ft_strjoin(get_env_var("HOME"), &name[1]);
	else if ((!ft_strncmp("./", name, 2)))
		path = ft_strjoin(get_env_var("PWD"), &name[1]);
	else if (name[0] == '/')
		path = ft_strdup(name);
	else
		path = search_in_path(name);
	return (path);
}

void	redir(t_token *token, t_prg *prg)
{
	char	*s1;
	char	*s2;
	int		in;
	int		out;

	out = 0;
	s1 = token->content;
	in = (*s1 >= '1' && *s1 <= '9') ? *s1 - '0' : 1;
	s2 = (*s1 >= '1' && *s1 <= '9') ? s1 + 3 : s1 + 2;
	if (*s2 && ft_strlen(s2) == 1)
	{
		if ((*s2 >= '1' && *s2 <= '9') || *s2 == '-')
			out = (*s2 == '-') ? open("/dev/null", O_WRONLY) : *s2 - '0';
	}
	if (in && out)
	{
		prg->r_in = in;
		prg->r_out = out;
	}
}

char	**arg_list_to_arr(t_list *args)
{
	char	**argv;
	size_t	len;
	size_t	i;

	if (!args || !(len = ft_lstlen(args)))
		return (NULL);
	argv = malloc(sizeof(char *) * len + 1);
	argv[len] = 0;
	i = 0;
	while (args && i < len)
	{
		argv[i] = ft_strdup(args->content);
		args = args->next;
		i++;
	}
	return (argv);
}
