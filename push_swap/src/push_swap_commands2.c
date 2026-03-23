/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:23 by leon              #+#    #+#             */
/*   Updated: 2026/03/23 14:36:55 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ra(x_list **a)
{
	x_list	*temp;
	x_list	*news;

	if (!(*a) || !(*a)->next)
		return (0);
	temp = (*a)->next;
	news = temp;
	while (temp->next)
		temp = temp->next;
	(*a)->next = NULL;
	temp->next = (*a);
	(*a) = news;
	write(1, "ra\n", 3);
	bench_conditional_increment((*a)->opts->bench, OP_RA);
	return (1);
}

int	rb(x_list **b)
{
	x_list	*temp;
	x_list	*news;

	if (!(*b) || !(*b)->next)
		return (0);
	temp = (*b)->next;
	news = temp;
	while (temp->next)
		temp = temp->next;
	(*b)->next = NULL;
	temp->next = (*b);
	(*b) = news;
	write(1, "rb\n", 3);
	bench_conditional_increment((*b)->opts->bench, OP_RB);
	return (1);
}

int	rr(x_list **a, x_list **b)
{
	x_list	*temp;
	x_list	*news;

	if (!(*a) || !(*a)->next)
		return (0);
	if (!(*b) || !(*b)->next)
		return (0);
	temp = (*a)->next;
	news = temp;
	while (temp->next)
		temp = temp->next;
	(*a)->next = NULL;
	temp->next = (*a);
	(*a) = news;
	temp = (*b)->next;
	news = temp;
	while (temp->next)
		temp = temp->next;
	(*b)->next = NULL;
	temp->next = (*b);
	(*b) = news;
	write(1, "rr\n", 3);
	bench_conditional_increment((*a)->opts->bench, OP_RR);
	return (1);
}
