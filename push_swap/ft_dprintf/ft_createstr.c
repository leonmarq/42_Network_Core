/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:39:52 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/22 11:02:54 by leonmarq         ###   ########.fr       */
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
char	*tobighex(unsigned long decnum)
{
	char	*res;
	long	i;
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

static
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
	{
		s = ft_calloc(2, 1);
		if (!s)
			return (NULL);
		if (c == 'c')
			s[0] = (char)va_arg(args, int);
		else
			s[0] = '%';
	}
	return (s);
}
