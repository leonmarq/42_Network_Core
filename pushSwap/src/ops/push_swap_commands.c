/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:56 by leon              #+#    #+#             */
/*   Updated: 2026/03/26 20:16:15 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	sa(t_slist *a)
{
	int	temp;

	if (!a)
		return (0);
	if (!a->next)
		return (0);
	temp = a->x;
	a->x = a->next->x;
	a->next->x = temp;
	write (1, "sa\n", 3);
	bench_conditional_increment(a->opts->bench, OP_SA);
	return (1);
}

int	sb(t_slist *b)
{
	int	temp;

	if (!b)
		return (0);
	if (!b->next)
		return (0);
	temp = b->x;
	b->x = b->next->x;
	b->next->x = temp;
	write (1, "sb\n", 3);
	bench_conditional_increment(b->opts->bench, OP_SB);
	return (1);
}

int	ss(t_slist *a, t_slist *b)
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
	write(1, "ss\n", 3);
	bench_conditional_increment(a->opts->bench, OP_SS);
	return (1);
}

int	pa(t_slist **a, t_slist **b)
{
	t_slist	*newb;

	if (!(*b))
		return (0);
	newb = (*b)->next;
	(*b)->next = (*a);
	(*a) = (*b);
	(*b) = newb;
	write(1, "pa\n", 3);
	bench_conditional_increment((*a)->opts->bench, OP_PA);
	return (1);
}

int	pb(t_slist **a, t_slist **b)
{
	t_slist	*newa;

	if (!(*a))
		return (0);
	newa = (*a)->next;
	(*a)->next = (*b);
	(*b) = (*a);
	(*a) = newa;
	write(1, "pb\n", 3);
	bench_conditional_increment((*b)->opts->bench, OP_PB);
	return (1);
}
