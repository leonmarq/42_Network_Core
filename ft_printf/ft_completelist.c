/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completelist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:39:44 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/22 16:03:12 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static
int	nbrprecision2(t_plist *list, char *s)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	if (list->sraw[i2] == '-')
	{
		s[i2++] = '-';
		i++;
	}
	while (list->precision > 0)
	{
		s[i2++] = '0';
		list->precision--;
	}
	while (list->sraw[i])
		s[i2++] = list->sraw[i++];
	free(list->sraw);
	list->sraw = s;
	return (1);
}

static
int	nbrprecision(t_plist *list)
{
	int		i;
	char	*s;

	i = 0;
	while (list->sraw[i])
		i++;
	if (list->precision == 0 && list->sraw[0] == '0')
		list->sraw[0] = '\0';
	if (list->sraw[0] == '-' && list->nul == 0)
		list->precision = list->precision + 1;
	if (list->precision <= i)
		return (1);
	s = ft_calloc(list->precision + 1, 1);
	if (!s)
		return (0);
	list->precision = list->precision - i;
	nbrprecision2(list, s);
	return (1);
}

static
int	strprecision(t_plist *list)
{
	int		i;

	i = 0;
	if (!list->sraw)
		return (0);
	while (list->sraw[i])
		i++;
	if (list->precision <= i && list->precision >= 0)
		list->sraw[list->precision] = '\0';
	return (1);
}

static
int	addspacing(t_plist *list)
{
	int		i;
	int		i2;

	list->s = ft_calloc(list->formatted_len + 1, 1);
	if (!list->s)
		return (0);
	i = 0;
	i2 = 0;
	if (!list->minus)
	{
		while (i < (list->formatted_len - (int)ft_strlen(list->sraw)))
			list->s[i++] = ' ';
	}
	while (list->sraw[i2])
		list->s[i++] = list->sraw[i2++];
	if (list->minus)
	{
		while (i < list->formatted_len)
			list->s[i++] = ' ';
	}
	return (1);
}

int	completelist(t_plist *list)
{
	while (list)
	{
		if (!list->sraw[0] && list->type == 'c')
			list->formatted_len--;
		if (findchrchr(list->type, PF_SET_NB) && list->precision >= 0)
		{
			if (!nbrprecision(list))
				return (0);
		}
		else if (list->type == 's' && list->precision >= 0)
		{
			if (!strprecision(list))
				return (0);
		}
		list->s = list->sraw;
		if (findchrchr(list->type, PF_SET_ALL)
			&& (list->formatted_len - (int)ft_strlen(list->sraw)) > 0)
		{
			if (!addspacing(list))
				return (0);
		}
		list = list->next;
	}
	return (1);
}
