/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:56 by leon              #+#    #+#             */
/*   Updated: 2026/03/20 10:20:45 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(x_list *a)
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
	return (1);
}

int	sb(x_list *b)
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
	return (1);
}

int	ss(x_list *a, x_list *b)
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
	return (1);
}

int	pa(x_list **a, x_list **b)
{
	x_list	*newb;

	if (!(*b))
		return (0);
	newb = (*b)->next;
	(*b)->next = (*a);
	(*a) = (*b);
	(*b) = newb;
	write(1, "pa\n", 3);
	return (1);
}

int	pb(x_list **a, x_list **b)
{
	x_list	*newa;

	if (!(*a))
		return (0);
	newa = (*a)->next;
	(*a)->next = (*b);
	(*b) = (*a);
	(*a) = newa;
	write(1, "pb\n", 3);
	return (1);
}
