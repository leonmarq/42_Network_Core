/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 15:50:39 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/22 15:51:10 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*tobighex(unsigned long decnum)
{
	char			*res;
	long			i;
	unsigned long	temp;

	i = 0;
	temp = decnum;
	while (temp != 0)
	{
		temp = temp / 16;
		i++;
	}
	res = ft_calloc(i + 2, 1);
	if (!res)
		return (NULL);
	if (decnum == 0)
		res[0] = '0';
	while (decnum != 0 && --i >= 0)
	{
		temp = decnum % 16;
		res[i] = 'A' + (temp - 10);
		if (temp < 10)
			res[i] = '0' + temp;
		decnum = decnum / 16;
	}
	return (res);
}

char	*tosmallhex(unsigned long decnum)
{
	char			*res;
	long			i;
	unsigned long	temp;

	i = 0;
	temp = decnum;
	while (temp != 0)
	{
		temp = temp / 16;
		i++;
	}
	res = ft_calloc(i + 2, 1);
	if (!res)
		return (NULL);
	if (decnum == 0)
		res[0] = '0';
	while (decnum != 0 && --i >= 0)
	{
		temp = decnum % 16;
		res[i] = 'a' + (temp - 10);
		if (temp < 10)
			res[i] = '0' + temp;
		decnum = decnum / 16;
	}
	return (res);
}
