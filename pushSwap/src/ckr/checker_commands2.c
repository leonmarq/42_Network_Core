/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_commands2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:17:48 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 11:53:14 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ra_ckr(t_slist **a)
{
	t_slist	*temp;
	t_slist	*news;

	if (!(*a) || !(*a)->next)
		return (0);
	temp = (*a)->next;
	news = temp;
	while (temp->next)
		temp = temp->next;
	(*a)->next = NULL;
	temp->next = (*a);
	(*a) = news;
	return (1);
}

int	rb_ckr(t_slist **b)
{
	t_slist	*temp;
	t_slist	*news;

	if (!(*b) || !(*b)->next)
		return (0);
	temp = (*b)->next;
	news = temp;
	while (temp->next)
		temp = temp->next;
	(*b)->next = NULL;
	temp->next = (*b);
	(*b) = news;
	return (1);
}

int	rr_ckr(t_slist **a, t_slist **b)
{
	t_slist	*temp;
	t_slist	*news;

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
	return (1);
}
