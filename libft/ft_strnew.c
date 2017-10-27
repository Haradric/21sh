/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:26:23 by mbraslav          #+#    #+#             */
/*   Updated: 2016/11/28 18:26:27 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	char	*res;

	str = ft_memalloc(size + 1);
	if (str == NULL)
		return (NULL);
	res = str;
	*(str + size) = '\0';
	while (*str)
		*str++ = '\0';
	return (res);
}
