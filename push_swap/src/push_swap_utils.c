/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:21 by leon              #+#    #+#             */
/*   Updated: 2026/03/25 12:39:03 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_free_list(x_list *a)
{
	x_list	*temp;

	if (!a)
		return (0);
	if (a->opts && a->opts->bench)
		free(a->opts->bench);
	while (a)
	{
		temp = a;
		a = a->next;
		free(temp);
	}
	return (0);
}

static
int	ft_atoicheck_init(int *i, int *x10, long *res)
{
	*i = 0;
	*x10 = 1;
	*res = 0;
	return (0);
}

long	ft_atoicheck(char *nptr)
{
	int			i;
	long		res;
	int			x10;

	ft_atoicheck_init(&i, &x10, &res);
	if (nptr[i] == '-')
		x10 = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (nptr[i] == '0' && nptr[i + 1] == '\0')
		return (0);
	if (!(nptr[i] > '0' && nptr[i] <= '9'))
		return ((long)2147483648);
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	if (nptr[i] || i-- > 11)
		return ((long)2147483648);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = ((nptr[i--] - '0') * x10) + res;
		x10 = x10 * 10;
	}
	if (res > (long)2147483647 || res < (long) -2147483648)
		return ((long)2147483648);
	return (res);
}

int	err(void)
{
	char	*s;
	int		i;

	s = "Error\n";
	i = 0;
	while (s[i])
	{
		write(2, &(s[i]), 1);
		i++;
	}
	return (-1);
}
