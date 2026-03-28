/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:37:36 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/25 13:55:15 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_last(t_slist *x)
{
	if (!x)
		return (0);
	while (x->next)
		x = x->next;
	return (x->x);
}

int	get_last_p(t_slist *x)
{
	if (!x)
		return (0);
	while (x->next)
		x = x->next;
	return (x->p);
}

int	get_biggest(t_slist *x)
{
	int	b;

	b = x->x;
	while (x->next)
	{
		x = x->next;
		if (b < x->x)
			b = x->x;
	}
	return (b);
}

int	get_size(t_slist *x)
{
	int	res;

	res = 0;
	while (x)
	{
		x = x->next;
		res++;
	}
	return (res);
}

t_slist	*get_index(t_slist *x, int p)
{
	int	i;

	i = 0;
	while (x && i++ < p)
		x = x->next;
	return (x);
}
