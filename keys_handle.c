/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 16:27:53 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/05 16:27:56 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	handle_shortcut(t_list **entry, t_term *term, unsigned long c)
{
	if (c == KEY_ALT_UP)
		cursor_str_up(*entry, term);
	else if (c == KEY_ALT_DOWN)
		cursor_str_down(*entry, term);
	else if (c == KEY_ALT_LEFT)
		cursor_word_left(*entry, term);
	else if (c == KEY_ALT_RIGHT)
		cursor_word_right(*entry, term);
}

void		key_handle(t_list **entry, t_term *term)
{
	unsigned long	c;

	c = 0;
	if (read(0, &c, sizeof(c)))
	{
		if (c == KEY_UP)
			hist_switch_to_entry(&(*entry), (*entry)->prev, term);
		else if (c == KEY_DOWN)
			hist_switch_to_entry(&(*entry), (*entry)->next, term);
		else if (c == KEY_LEFT)
			key_handle_left(*entry, term);
		else if (c == KEY_RIGHT)
			key_handle_right((*entry), term);
		else if (c == KEY_DEL)
			key_handle_delete(*entry, term);
		else if (c == KEY_HOME)
			cursor_to_start(*entry, term);
		else if (c == KEY_END)
			cursor_to_end(*entry, term);
		else
			handle_shortcut(entry, term, c);
	}
}

void		key_handle_left(t_list *entry, t_term *term)
{
	if (entry->content && term->cursor && entry->content != term->cursor)
	{
		cursor_move(entry, -1, term);
		term->cursor--;
	}
}

void		key_handle_right(t_list *entry, t_term *term)
{
	if (entry->content && term->cursor && *(term->cursor))
	{
		cursor_move(entry, 1, term);
		term->cursor++;
	}
}
