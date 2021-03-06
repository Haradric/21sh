/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:25:06 by mbraslav          #+#    #+#             */
/*   Updated: 2016/11/28 18:25:12 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int		i;

	if (!s)
		return ;
	i = 0;
	while (*(s + i))
	{
		f(i, s + i);
		i++;
	}
}
