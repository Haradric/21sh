/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:40:57 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/14 14:40:59 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_list	*hist_new_entry(void)
{
	t_list	*entry;

	entry = ft_lstnew(NULL, 0);
	entry->content = ft_memalloc(BUFF_SIZE);
	entry->content_size = BUFF_SIZE;
	return (entry);
}

t_list	*hist_add_entry(t_list **hist)
{
	t_list	*new_entry;

	if (!*hist)
		return ((*hist = hist_new_entry()));
	new_entry = hist_new_entry();
	ft_lstpushback(hist, new_entry);
	while (ft_lstlen(*hist) > HIST_SIZE + 1)
		ft_lstfreeelem(hist, *hist, free);
	return (new_entry);
}

void	hist_switch_to_entry(t_list **current, t_list *new, t_term *term)
{
	int		len;
	int		i;

	if (!new)
		return ;
	len = (int)term->cursor - (int)(*current)->content;
	cursor_move(*current, -len, term);
	len = (int)ft_strlen((*current)->content);
	i = 0;
	while (i++ < len)
		ft_putchar(' ');
	cursor_move(*current, -len, term);
	ft_putstr(new->content);
	term->cursor = ft_strchr(new->content, 0);
	*current = new;
}
