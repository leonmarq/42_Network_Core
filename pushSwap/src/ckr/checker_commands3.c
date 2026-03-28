/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_commands3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:17:51 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/27 15:17:52 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	rra_ckr(t_slist **a)
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
	return (1);
}

int	rrb_ckr(t_slist **b)
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
	return (1);
}
