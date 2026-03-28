/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:17:45 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/27 15:17:47 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	sa_ckr(t_slist *a)
{
	int	temp;

	if (!a)
		return (0);
	if (!a->next)
		return (0);
	temp = a->x;
	a->x = a->next->x;
	a->next->x = temp;
	return (1);
}

int	sb_ckr(t_slist *b)
{
	int	temp;

	if (!b)
		return (0);
	if (!b->next)
		return (0);
	temp = b->x;
	b->x = b->next->x;
	b->next->x = temp;
	return (1);
}

int	ss_ckr(t_slist *a, t_slist *b)
{
	int	temp;

	if (!a || !b)
		return (0);
	if (!a->next || !b->next)
		return (0);
	temp = b->x;
	b->x = b->next->x;
	b->next->x = temp;
	temp = a->x;
	a->x = a->next->x;
	a->next->x = temp;
	return (1);
}

int	pa_ckr(t_slist **a, t_slist **b)
{
	t_slist	*newb;

	if (!(*b))
		return (0);
	newb = (*b)->next;
	(*b)->next = (*a);
	(*a) = (*b);
	(*b) = newb;
	return (1);
}

int	pb_ckr(t_slist **a, t_slist **b)
{
	t_slist	*newa;

	if (!(*a))
		return (0);
	newa = (*a)->next;
	(*a)->next = (*b);
	(*b) = (*a);
	(*a) = newa;
	return (1);
}
