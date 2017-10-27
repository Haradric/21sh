/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handle2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 17:08:05 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/06 17:08:07 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void		key_handle_backspace(t_list *entry, t_term *term)
{
	if (entry->content && term->cursor && entry->content != term->cursor)
	{
		term->cursor = remove_from_entry(entry, term->cursor);
		cursor_move(entry, -1, term);
		ft_putstr(term->cursor);
		ft_putchar(' ');
		cursor_move(entry, -((int)ft_strlen(term->cursor) + 1), term);
	}
}

void		key_handle_delete(t_list *entry, t_term *term)
{
	if (entry->content && term->cursor && *(term->cursor))
	{
		term->cursor = remove_from_entry(entry, term->cursor + 1);
		ft_putstr(term->cursor);
		ft_putchar(' ');
		cursor_move(entry, -((int)ft_strlen(term->cursor) + 1), term);
	}
}
