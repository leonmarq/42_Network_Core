/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:29:04 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/25 13:55:11 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_biggest_p(t_slist *x)
{
	int	biggest;

	if (!x)
		return (0);
	biggest = x->p;
	while (x)
	{
		if (x->p > biggest)
			biggest = x->p;
		x = x->next;
	}
	return (biggest);
}

int	get_size_end_p(t_slist *x)
{
	t_slist	*tmp;
	int		p;
	int		res;

	if (!x)
		return (0);
	tmp = x;
	while (tmp->next)
		tmp = tmp->next;
	p = tmp->p;
	while (x && x->p != p)
		x = x->next;
	res = 0;
	while (x)
	{
		x = x->next;
		res++;
	}
	return (res);
}

int	get_size_p(t_slist *x)
{
	int	res;
	int	p;

	res = 0;
	p = x->p;
	while (x && x->p == p)
	{
		x = x->next;
		res++;
	}
	return (res);
}
