/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 17:59:30 by mbraslav          #+#    #+#             */
/*   Updated: 2017/07/31 17:59:31 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_token(void *token)
{
	t_token	*ptr;

	if (!token)
		return ;
	ptr = (t_token *)token;
	if (ptr->content)
		free(ptr->content);
	free(token);
}

void	free_prg(void *prg)
{
	t_prg	*ptr;

	if (!prg)
		return ;
	ptr = prg;
	if (ptr->path)
		free(ptr->path);
	if (ptr->argv)
		free_str_array(ptr->argv);
	free(prg);
}

void	free_str_array(char **arr)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
