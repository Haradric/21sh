/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:50:56 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/26 16:50:57 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	cursor_move(t_list *entry, int spaces, t_term *term)
{
	int		abs_spaces;
	int		pos;
	int		i;

	if (!entry->content || !spaces)
		return ;
	interrogate_terminal(term);
	abs_spaces = (spaces >= 0) ? spaces : -spaces;
	pos = (int)ft_strlen(term->prompt) + \
								(int)(term->cursor - (char *)entry->content);
	while (abs_spaces)
	{
		if (spaces > 0 && !((pos + 1) % term->cols))
		{
			ft_putstr("\033[B");
			i = term->cols;
			while (--i)
				ft_putstr("\033[D");
		}
		else
			(spaces > 0) ? ft_putstr("\033[C") : \
			ft_putstr("\033[D");
		(spaces > 0) ? pos++ : pos--;
		abs_spaces--;
	}
}

void	cursor_to_start(t_list *entry, t_term *term)
{
	if (!term->cursor || !entry->content)
		return ;
	while (term->cursor > (char *)entry->content)
	{
		cursor_move(entry, -1, term);
		term->cursor--;
	}
}

void	cursor_to_end(t_list *entry, t_term *term)
{
	if (!term->cursor || !entry->content)
		return ;
	while (*term->cursor)
	{
		cursor_move(entry, 1, term);
		term->cursor++;
	}
}

void	cursor_word_left(t_list *entry, t_term *term)
{
	char	*cursor;

	if (!entry->content || !term->cursor)
		return ;
	cursor = term->cursor;
	while ((entry->content != cursor) && ft_isspace(*(cursor - 1)))
		cursor--;
	while ((entry->content != cursor) && !ft_isspace(*(cursor - 1)))
		cursor--;
	while ((entry->content != cursor) && ft_isspace(*(cursor - 1)))
		cursor--;
	cursor_move(entry, (int)(cursor - term->cursor), term);
	term->cursor = cursor;
}

void	cursor_word_right(t_list *entry, t_term *term)
{
	char	*cursor;

	if (!entry->content || !term->cursor)
		return ;
	cursor = term->cursor;
	while (*cursor && ft_isspace(*cursor))
		cursor++;
	while (*cursor && !ft_isspace(*cursor))
		cursor++;
	cursor_move(entry, (int)(cursor - term->cursor), term);
	term->cursor = cursor;
}
