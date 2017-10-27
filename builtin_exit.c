/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 16:06:53 by mbraslav          #+#    #+#             */
/*   Updated: 2017/08/09 16:06:54 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	builtin_exit(int argc, char **argv)
{
	if (argc == 1 && argv[1] == 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
