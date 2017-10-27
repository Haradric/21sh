/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 15:44:13 by mbraslav          #+#    #+#             */
/*   Updated: 2017/08/29 15:44:14 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	replace(char **str, char *s)
{
	size_t	len;
	char	*ret;
	char	*start;
	char	*mid;
	char	*tmp;

	len = 0;
	while (*(s + len + 1) >= 'A' && *(s + len + 1) <= 'Z')
		len++;
	tmp = ft_strsub(s + 1, 0, len);
	mid = get_env_var(tmp);
	free(tmp);
	start = ft_strsub(*str, 0, s - *str);
	if (mid)
		tmp = ft_strjoin(mid, s + 1 + len);
	else
		tmp = ft_strdup(s + 1 + len);
	ret = ft_strjoin(start, tmp);
	free(start);
	free(tmp);
	free(*str);
	*str = ret;
}

void		env_replace(t_list *elem)
{
	int		quotes;
	char	**str;
	char	*s;

	str = &((t_token *)elem->content)->content;
	s = *str;
	quotes = 0;
	while (s && *s)
	{
		quotes = (*s == '\'') ? !quotes : quotes;
		if (!quotes && *s == '$')
		{
			replace(str, s);
			s = *str;
			continue ;
		}
		s++;
	}
}

void		quotes_remove(t_list *elem)
{
	int		quotes;
	char	*s1;
	char	*s2;
	char	c;

	quotes = 0;
	c = 0;
	if (!(s1 = ((t_token *)elem->content)->content) || \
		!(ft_strchr(s1, '\'') || ft_strchr(s1, '\"')))
		return ;
	s2 = s1;
	while (*s2)
	{
		if (((*s2 == '\'' || *s2 == '\"') && !quotes) || \
			((*s2 == '\'' || *s2 == '\"') && quotes && *s2 == c))
		{
			c = *s2;
			quotes = !quotes;
			s2++;
			continue ;
		}
		*s1++ = *s2++;
	}
	while (s1 != s2)
		*(s1++) = 0;
}
