/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 16:10:11 by mbraslav          #+#    #+#             */
/*   Updated: 2017/08/09 16:10:12 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	terminate(const char *error_msg, const char *str)
{
	error(error_msg, str);
	exit(EXIT_FAILURE);
}

void	error(const char *error_msg, const char *str)
{
	write(2, error_msg, ft_strlen(error_msg));
	write(2, " ", 1);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	ft_perror(const char *error_msg, const char *str)
{
	const char	*msg[] = {"operation not permitted", "no such file or \
directory", "no such process", "interrupted system call", "input/output \
error", "device not configured", "argument list too long", "exec format \
error", "bad file descriptor", "no child processes", "resource deadlock \
avoided", "cannot allocate memory", "permission denied", "bad address", "block \
device required", "device / resource busy", "file exists", "cross-device \
link", "operation not supported by device", "not a directory", "is a \
directory", "invalid argument", "too many open files in system", "too many \
open files", "inappropriate ioctl for device", "text file busy", "file too \
large", "no space left on device", "illegal seek", "read-only file system", \
"too many links", "broken pipe"};

	write(2, error_msg, ft_strlen(error_msg));
	write(2, " ", 1);
	if (errno < 32)
		write(2, msg[errno - 1], ft_strlen(msg[errno - 1]));
	else
		write(2, "unknown error", 13);
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
