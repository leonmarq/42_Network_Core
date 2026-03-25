/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:26 by leon              #+#    #+#             */
/*   Updated: 2026/03/25 13:25:40 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rra(t_slist **a)
{
	t_slist	*temp;

	if (!(*a) || !(*a)->next)
		return (0);
	temp = (*a);
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = (*a);
	(*a) = temp->next;
	temp->next = NULL;
	write(1, "rra\n", 4);
	bench_conditional_increment((*a)->opts->bench, OP_RRA);
	return (1);
}

int	rrb(t_slist **b)
{
	t_slist	*temp;

	if (!(*b) || !(*b)->next)
		return (0);
	temp = (*b);
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = (*b);
	(*b) = temp->next;
	temp->next = NULL;
	write(1, "rrb\n", 4);
	bench_conditional_increment((*b)->opts->bench, OP_RRB);
	return (1);
}

int	rrr(t_slist **a, t_slist **b)
{
	t_slist	*temp;

	if (!(*a) || !(*a)->next)
		return (0);
	if (!(*b) || !(*b)->next)
		return (0);
	temp = (*a);
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = (*a);
	(*a) = temp->next;
	temp->next = NULL;
	temp = (*b);
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = (*b);
	(*b) = temp->next;
	temp->next = NULL;
	write(1, "rrr\n", 4);
	bench_conditional_increment((*a)->opts->bench, OP_RRR);
	return (1);
}
