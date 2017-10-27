/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:46:16 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/14 14:46:18 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_terminal_data(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (!termtype)
		terminate("21sh:", "Specify a terminal type with 'setenv TERM \
			termtype'.");
	success = tgetent(NULL, termtype);
	if (success < 0)
		terminate("21sh:", "Could not access the termcap data base");
	else if (success == 0)
		terminate("21sh: Terminal type is not defined:", termtype);
}

void	interrogate_terminal(t_term *info)
{
	struct winsize	ws;

	if (ioctl(1, TIOCGWINSZ, &ws))
		terminate("21sh:", "an error occured.");
	info->rows = ws.ws_row;
	info->cols = ws.ws_col;
}
