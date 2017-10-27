/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 16:25:05 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/05 16:25:07 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	newline_validate(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && !ft_strcmp(str + len - 2, "\\\n"))
	{
		str[len - 2] = 0;
		str[len - 1] = 0;
		return (1);
	}
	return (0);
}

static int	quotes_validate(char *str)
{
	char	*next;
	char	*s;

	s = str;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (!(next = ft_strchr(s + 1, *s)))
				return (*s);
			s = next;
		}
		s++;
	}
	return (0);
}

static void	get_additional_input(const char *prompt, t_list *entry)
{
	t_list	*tmplist;
	t_term	tmpterm;
	char	*new_input;

	interrogate_terminal(&tmpterm);
	tmpterm.prompt = (char *)prompt;
	tmplist = NULL;
	tmpterm.entry = hist_add_entry(&tmplist);
	ft_putstr(prompt);
	read_input(&tmpterm);
	new_input = tmplist->content;
	while (*new_input)
		add_to_entry(entry, *new_input++, ft_strrchr(entry->content, 0));
	ft_lstfreelist(&tmplist, free);
}

void		input_validate(t_list *entry)
{
	const char	*prompt1 = "> ";
	const char	*prompt2 = "quote> ";
	const char	*prompt3 = "dquote> ";
	int			c;

	c = 1;
	while (!entry->content || (c = newline_validate(entry->content)) || \
(c = quotes_validate(entry->content)))
	{
		if (!entry->content || c == 1)
			get_additional_input(prompt1, entry);
		if (!entry->content || c == '\'')
			get_additional_input(prompt2, entry);
		if (!entry->content || c == '\"')
			get_additional_input(prompt3, entry);
	}
	*(char *)(entry->content + ft_strlen(entry->content) - 1) = 0;
}
