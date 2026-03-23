/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:39:52 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/23 09:12:41 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

char	*nbtostr(long long n)
{
	char	*res;
	long	i;

	if (!n)
		return (ft_strdup("0"));
	i = 0;
	if (n < 0)
		i++;
	i = i + dividecount(n);
	res = ft_calloc(i + 1, 1);
	if (n < 0)
	{
		n = n * -1;
		res[0] = '-';
	}
	while (n)
	{
		res[--i] = (n % 10) + '0';
		n = n / 10;
	}
	return (res);
}

static
char	*ptostr(char *ptr)
{
	int		i;
	char	*s;
	char	*res;

	if (!ptr)
		return (ft_strdup("(nil)"));
	i = 0;
	s = tosmallhex((unsigned long) ptr);
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	res = (char *)ft_calloc (i + 3, 1);
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = 'x';
	i = 0;
	while (s[i])
	{
		res[i + 2] = s[i];
		i++;
	}
	free (s);
	return (res);
}

char	*handle_c_or_percent(va_list args, char c)
{
	char	*s;

	s = ft_calloc(2, 1);
	if (!s)
		return (NULL);
	if (c == 'c')
		s[0] = (char)va_arg(args, int);
	else
		s[0] = '%';
	return (s);
}

char	*createstr(va_list args, char c)
{
	char	*s;
	char	*t;

	s = NULL;
	if (c == 'd' || c == 'i')
		s = nbtostr(va_arg(args, int));
	else if (c == 'u')
		s = nbtostr(va_arg(args, unsigned));
	else if (c == 's')
	{
		t = va_arg(args, char *);
		if (!t)
			t = "(null)";
		s = ft_strdup(t);
	}
	else if (c == 'p')
		s = ptostr(va_arg(args, void *));
	else if (c == 'x')
		s = tosmallhex(va_arg(args, unsigned));
	else if (c == 'X')
		s = tobighex(va_arg(args, unsigned));
	else if (c == 'c' || c == '%')
		s = handle_c_or_percent(args, c);
	return (s);
}
