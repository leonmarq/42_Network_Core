/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:21 by leon              #+#    #+#             */
/*   Updated: 2026/03/27 18:12:41 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	p_to_x(t_slist **stack)
{
	t_slist	*current;

	current = *stack;
	while (current)
	{
		current->x = current->p;
		current->p = 0;
		current = current->next;
	}
	return (0);
}

int	ps_free_list(t_slist *a)
{
	t_slist	*temp;

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
int	ft_atoicheck_init(long long *x10, long long *res, char *nptr)
{
	int	i;

	i = 0;
	*x10 = 1;
	*res = 0;
	if (nptr[i] == '-')
		*x10 = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	return (i);
}

long	ft_atoicheck(char *nptr)
{
	int			i;
	long long	res;
	long long	x10;

	if (!nptr || !*nptr)
		return ((long)2147483648);
	i = ft_atoicheck_init(&x10, &res, nptr);
	if (nptr[i] == '0' && nptr[i + 1] == '\0')
		return (0);
	if (!(nptr[i] > '0' && nptr[i] <= '9'))
		return ((long)2147483648);
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	if (nptr[i] || i-- > 11)
		return ((long)2147483648);
	while (i >= 0 && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = ((nptr[i--] - '0') * x10) + res;
		x10 = x10 * 10;
	}
	if (res > (long long)2147483647 || res < (long long) -2147483648)
		return ((long)2147483648);
	return ((long)res);
}
