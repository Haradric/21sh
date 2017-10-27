/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 15:02:49 by mbraslav          #+#    #+#             */
/*   Updated: 2017/08/22 15:02:50 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	write_to_file(int fd, const char *eol)
{
	t_list	*hist;
	char	*tmp;

	hist = NULL;
	while (ft_strcmp(eol, tmp = get_input("heredoc> ", &hist)))
	{
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
	}
	ft_lstfreelist(&hist, free);
}

int			heredoc(char *eol)
{
	char	*path;
	int		fd;

	if (!eol)
		return (-1);
	path = ft_strjoin(get_env_var("TMPDIR"), "heredoc");
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		ft_perror("21sh:", path);
		free(path);
		return (-1);
	}
	write_to_file(fd, eol);
	close(fd);
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_perror("21sh:", path);
		free(path);
		return (-1);
	}
	free(path);
	return (fd);
}
