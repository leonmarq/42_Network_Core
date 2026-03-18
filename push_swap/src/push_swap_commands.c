/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:56 by leon              #+#    #+#             */
/*   Updated: 2022/04/08 15:37:01 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(t_list *a)
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

int	sb(t_list *b)
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

int	ss(t_list *a, t_list *b)
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

int	pa(t_list **a, t_list **b)
{
	t_list	*newb;

	if (!(*b))
		return (0);
	newb = (*b)->next;
	(*b)->next = (*a);
	(*a) = (*b);
	(*b) = newb;
	write(1, "pa\n", 3);
	return (1);
}

int	pb(t_list **a, t_list **b)
{
	t_list	*newa;

	if (!(*a))
		return (0);
	newa = (*a)->next;
	(*a)->next = (*b);
	(*b) = (*a);
	(*a) = newa;
	write(1, "pb\n", 3);
	return (1);
}
