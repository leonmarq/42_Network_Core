/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:27 by leon              #+#    #+#             */
/*   Updated: 2026/03/18 20:16:39 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	p_to_null(t_list *a)
{
	while (a)
	{
		a->p = 0;
		a = a->next;
	}
	return (0);
}

int	sorted(t_list *a)
{
	if (!a)
		return (1);
	if (!(a->next))
		return (1);
	while (a->next)
	{
		if (a->x > a->next->x)
			return (0);
		a = a->next;
	}
	p_to_null(a);
	return (1);
}

int	get_last(t_list *x)
{
	if (!x)
		return (0);
	while (x->next)
		x = x->next;
	return (x->x);
}

int	get_last_p(t_list *x)
{
	if (!x)
		return (0);
	while (x->next)
		x = x->next;
	return (x->p);
}

int	get_biggest(t_list *x)
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
