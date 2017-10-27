/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 16:24:53 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/05 16:24:54 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	cursor_str_up(t_list *entry, t_term *term)
{
	size_t	len;

	interrogate_terminal(term);
	len = (int)(term->cursor - (char *)entry->content);
	if ((int)len >= term->cols)
	{
		cursor_move(entry, -term->cols, term);
		term->cursor -= term->cols;
	}
}

void	cursor_str_down(t_list *entry, t_term *term)
{
	size_t	len;

	interrogate_terminal(term);
	len = ft_strlen(term->cursor);
	if ((int)len >= term->cols)
	{
		cursor_move(entry, term->cols, term);
		term->cursor += term->cols;
	}
}
