/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:47:14 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/14 14:47:14 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "shell.h"

t_term		*g_term;

char		*get_input(const char *prompt, t_list **hist)
{
	static struct termios	default_settings;
	t_term					term;
	t_list					*hist_dup;
	t_list					*tmp;

	ft_memset(&term, 0, sizeof(t_term));
	init_terminal_data();
	term.prompt = (char *)prompt;
	enable_keypress(&default_settings);
	hist_dup = ft_lstdup(*hist);
	term.entry = hist_add_entry(&hist_dup);
	ft_putstr(term.prompt);
	read_input(&term);
	input_validate(term.entry);
	if ((tmp = ft_lstfind(*hist, term.entry->content, \
												term.entry->content_size)))
		ft_lstfreeelem(hist, tmp, free);
	if (!ft_strcmp(term.entry->content, "") || is_empty(term.entry->content))
		term.entry = NULL;
	ft_lstremoveelem(&hist_dup, term.entry);
	ft_lstfreelist(&hist_dup, free);
	ft_lstpushback(hist, term.entry);
	disable_keypress(&default_settings);
	return ((term.entry) ? term.entry->content : NULL);
}

void		read_input(t_term *term)
{
	char	c;

	term->cursor = ft_strchr(term->entry->content, 0);
	g_term = term;
	signal(SIGINT, signal_handler_input);
	signal(SIGQUIT, signal_handler_input);
	while (read(0, &c, 1))
	{
		if (c == '\n')
			break ;
		else if (c == KEY_ESC)
			key_handle(&(term->entry), term);
		else if (c == KEY_BACKSPACE)
			key_handle_backspace(term->entry, term);
		else if (c == '\t')
			;
		else if (c)
			edit_entry(c, term->entry, term);
		c = 0;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_putstr(term->cursor);
	add_to_entry(term->entry, '\n', NULL);
	ft_putchar('\n');
}

char		*add_to_entry(t_list *entry, char c, char *cursor)
{
	size_t	diff;
	char	*new;

	if (!cursor)
		cursor = ft_strchr(entry->content, 0);
	while (entry->content_size <= ft_strlen(entry->content) + 1)
	{
		diff = (void *)cursor - entry->content;
		new = ft_memalloc(entry->content_size + BUFF_SIZE);
		ft_memccpy(new, entry->content, 0, entry->content_size);
		free(entry->content);
		cursor = new + diff;
		entry->content = new;
		entry->content_size += BUFF_SIZE;
	}
	if (*cursor)
		ft_memmove(cursor + 1, cursor, ft_strlen(cursor));
	*cursor = c;
	return (cursor);
}

char		*remove_from_entry(t_list *entry, char *cursor)
{
	if (cursor != entry->content)
		ft_memcpy(cursor - 1, cursor, ft_strlen(cursor));
	cursor[ft_strlen(cursor) - 1] = 0;
	return (--cursor);
}

void		edit_entry(char c, t_list *entry, t_term *term)
{
	int		len;

	term->cursor = add_to_entry(entry, c, term->cursor);
	ft_putstr(term->cursor);
	len = -(int)(ft_strlen(term->cursor) - 1);
	cursor_move(entry, len, term);
	term->cursor++;
}
