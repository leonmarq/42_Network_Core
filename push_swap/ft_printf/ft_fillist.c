/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:39:59 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/17 09:33:48 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static
int	listputprecision(x_list *list, const char *format, int i, va_list args)
{
	i++;
	if (findchr(format, i, list->setnocp))
		list->precision = 0;
	else if (format[i] == '*')
	{
		list->precision = va_arg(args, int);
		i++;
	}
	else if (format[i] >= '0' && format[i] <= '9')
		list->precision = strtonb(format, &i);
	if (findchr(format, i, list->setnocp))
		list->type = format[i++];
	else
		return (0);
	return (i);
}

static
int	listputformat2(x_list *list, const char *format, int i, va_list args)
{
	if (format[i] == '-')
		list->minus = 1;
	if (format[i] == '-')
		i++;
	if (format[i] == '*')
	{
		list->nbr = va_arg(args, int);
		if (list->nbr < 0)
		{
			list->nbr = list->nbr * -1;
			list->minus = 1;
		}
		i++;
	}
	else if (format[i] >= '0' && format[i] <= '9')
		list->nbr = strtonb(format, &i);
	if (findchr(format, i, list->set))
		list->type = format[i++];
	else if (format[i] == '.')
		i = listputprecision(list, format, i, args);
	else
		i = 0;
	if (i != 0)
		list->sraw = createstr(args, list->type);
	return (i);
}

static
int	listputformat(x_list *list, const char *format, int i, va_list args)
{
	if (format[++i] == '0')
	{
		list->nul = 1;
		if (format[++i] == '*')
		{
			list->precision = va_arg(args, int);
			i++;
		}
		else if (format[i] >= '0' && format[i] <= '9')
			list->precision = strtonb(format, &i);
		if (format[i] == '.')
		{
			list->nbr = list->precision;
			list->nul = 0;
			i = listputprecision(list, format, i, args);
		}
		else if (findchr(format, i, list->setnb))
			list->type = format[i++];
		else
			return (0);
		list->sraw = createstr(args, list->type);
	}
	else
		i = listputformat2(list, format, i, args);
	return (i);
}

int	filllist(x_list *list, const char *format, va_list args)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (!format[i])
		list->sraw = ft_strdup("");
	while (format[i])
	{
		if (format[i] != '%')
		{
			while (format[i] != '%' && format[i])
				i++;
			list->sraw = ft_substr(format, start, (i - start));
		}
		else
			i = listputformat(list, format, i, args);
		start = i;
		if (i <= 0)
			return (0);
		if (format[i])
			list->next = emptylist();
		list = list->next;
	}
	return (1);
}
