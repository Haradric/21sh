/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:51:07 by mbraslav          #+#    #+#             */
/*   Updated: 2017/06/26 16:51:09 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	enable_keypress(struct termios *settings)
{
	struct termios new_settings;

	tcgetattr(0, settings);
	new_settings = *settings;
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	return ;
}

void	disable_keypress(struct termios *settings)
{
	tcsetattr(0, TCSANOW, settings);
	return ;
}

ssize_t	get_key(char *buff, size_t size)
{
	ft_memset(buff, 0, size);
	return (read(0, buff, size));
}
