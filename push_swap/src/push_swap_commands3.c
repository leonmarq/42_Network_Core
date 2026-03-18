/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:26 by leon              #+#    #+#             */
/*   Updated: 2022/04/08 15:36:28 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rra(t_list **a)
{
	t_list	*temp;

	if (!(*a) || !(*a)->next)
		return (0);
	temp = (*a);
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = (*a);
	(*a) = temp->next;
	temp->next = NULL;
	write(1, "rra\n", 4);
	return (1);
}

int	rrb(t_list **b)
{
	t_list	*temp;

	if (!(*b) || !(*b)->next)
		return (0);
	temp = (*b);
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = (*b);
	(*b) = temp->next;
	temp->next = NULL;
	write(1, "rrb\n", 4);
	return (1);
}

int	rrr(t_list **a, t_list **b)
{
	t_list	*temp;

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
	return (1);
}
