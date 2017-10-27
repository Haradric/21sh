/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 17:43:46 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/31 17:43:48 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token	*token_create(const char *str, size_t len)
{
	t_token	*token;
	char	*s;

	if (!str || !(token = ft_memalloc(sizeof(t_token))))
		return (NULL);
	s = ft_strsub(str, 0, len);
	token->type = OPERATOR;
	if (!ft_strcmp("<<", s))
		token->op = REDIR2_L;
	else if (!ft_strcmp("<", s))
		token->op = REDIR_L;
	else if (!ft_strcmp(">>", s))
		token->op = REDIR2_R;
	else if (!ft_strcmp(">", s))
		token->op = REDIR_R;
	else if (!ft_strcmp(";", s))
		token->op = SEMICOLON;
	else if (!ft_strcmp("|", s))
		token->op = PIPE;
	else
		token->type = STRING;
	if (token->type == STRING)
		token->content = ft_strdup(s);
	free(s);
	return (token);
}

static t_token	*get_next_token(const char *str)
{
	static char	*string;
	char		*s;
	t_token		*token;

	if (str)
	{
		string = (char *)str;
		return (NULL);
	}
	while (*string == ' ')
		string++;
	s = string;
	while (*s && *s != ' ')
	{
		if (*s == '\'' || *s == '\"')
			s = ft_strchr(s + 1, *s);
		s++;
	}
	if (s == string)
		return (NULL);
	token = token_create(string, s - string);
	string = s;
	return (token);
}

t_list			*get_token_list(const char *str)
{
	t_list	*list;
	t_list	*elem;
	t_token	*token;

	if (!str)
		return (NULL);
	list = NULL;
	get_next_token(str);
	while ((token = get_next_token(NULL)))
	{
		elem = ft_lstnew(NULL, 0);
		elem->content = token;
		ft_lstpushback(&list, elem);
	}
	ft_lstiter(list, env_replace);
	ft_lstiter(list, quotes_remove);
	return (list);
}
