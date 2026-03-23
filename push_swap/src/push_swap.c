/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:20 by leon              #+#    #+#             */
/*   Updated: 2026/03/23 09:23:44 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	sort5_2smaltob(x_list **a, x_list **b, int count)
{
	int		i2;
	int		x;
	x_list	*tmp;

	while (--count > -1)
	{
		i2 = 0;
		x = INT32_MAX;
		tmp = (*a);
		while (tmp)
		{
			if (tmp->x < x)
				x = tmp->x;
			tmp = tmp->next;
			i2++;
		}
		while ((*a)->x != x && i2 < 2)
			ra(a);
		while ((*a)->x != x && i2 >= 2)
			rra(a);
		pb(a, b);
	}
	return (0);
}

static
int	sort5(x_list **a, x_list **b)
{
	int		size;
	x_list	*tmp;

	size = 0;
	tmp = *a;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	if (size > 3)
		sort5_2smaltob(a, b, (size - 3));
	if ((*a)->x > (*a)->next->x && (*a)->x > (*a)->next->next->x)
		ra(a);
	if ((*a)->next->x > (*a)->next->next->x && (*a)->x < (*a)->next->x)
		rra(a);
	if ((*a)->x > (*a)->next->x)
		sa(*a);
	pa(a, b);
	pa(a, b);
	return (0);
}

int	pnx_algorithm(x_list **a, x_list **b, int strat)
{
	if (strat == SIMPLE)
		return (algorithm_simple(a, b));
	else if (strat == MEDIUM)
		return (algorithm_medium(a, b));
	else if (strat == COMPLEX || strat == DEFAULT || strat == ADAPTIVE)
		return (algorithm_complex(a, b));
	return (0);
}

int	push_swap(x_list **a, x_list **b)
{
	x_list	*temp;
	int		i;

	temp = *a;
	while (temp)
	{
		if (!(temp->next))
			return (0);
		if (temp->next->x < temp->x)
			break ;
		temp = temp->next;
	}
	temp = *a;
	i = get_size(*a);
	if (i == 2)
	{
		if ((*a)->x > (*a)->next->x)
			sa(*a);
	}
	else if (i <= 5 && i > 2)
		sort5(a, b);
	else
		pnx_algorithm(a, b, (*a)->opts->strat);
	return (0);
}
