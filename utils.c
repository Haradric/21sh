/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:46:52 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/14 14:46:52 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*str_to_list(char *str)
{
	t_list	*list;

	list = NULL;
	while (*str)
	{
		ft_lstpushback(&list, ft_lstnew(str, 1));
		str++;
	}
	return (list);
}

char	*list_to_str(t_list *list)
{
	char	*str;
	char	*s;
	t_list	*elem;

	str = (char *)ft_memalloc(ft_lstlen(list) + 1);
	s = str;
	elem = list;
	while (elem)
	{
		*s = *(char *)elem->content;
		elem = elem->next;
		s++;
	}
	return (str);
}

int		is_op(char c)
{
	return ((c == '|' || c == '<' || c == '>' || c == ';') ? 1 : 0);
}

int		is_dir(const char *path)
{
	struct stat	filestat;

	if (stat(path, &filestat) == -1)
		return (-1);
	if ((filestat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	else
		return (0);
}

int		is_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}
