/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:31 by leon              #+#    #+#             */
/*   Updated: 2026/03/24 10:48:34 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort3_a(x_list **a, x_list **b, int k)
{
	if (k == 2)
	{
		if ((*a)->x > (*a)->next->x)
			sa(*a);
		return (0);
	}
	else if (k == 3)
	{
		if ((*a)->x > (*a)->next->x && (*a)->x > (*a)->next->next->x)
			sa(*a);
		if ((*a)->next->x > (*a)->next->next->x && (*a)->x < (*a)->next->x)
		{
			pb(a, b);
			sa(*a);
			pa(a, b);
		}
		if ((*a)->x > (*a)->next->x)
			sa(*a);
	}
	return (0);
}

int sort2_b_pa(x_list **a, x_list **b)
{
	if ((*b)->x < (*b)->next->x)
		sb(*b);
	pa(a, b);
	pa(a, b);
	p_to_null(*a);
	return (0);
}

int	sort3_b_pa(x_list **a, x_list **b, int k)
{
	if (k <= 2)
		return (sort2_b_pa(a, b));
	else if (k == 3)
	{
		if ((*b)->next->next-> x > (*b)->x && (*b)->next->next->x > (*b)->next->x)
		{
			rb(b);
			if ((*b)->x < (*b)->next->x)
				sb(*b);
			pa(a, b);
			pa(a, b);
			rrb(b);
			pa(a, b);
		}
		else if ((*b)->next->x > (*b)->x && (*b)->next->x > (*b)->next->next->x)
		{
			if ((*b)->x < (*b)->next->x)
				sb(*b);
			pa(a, b);
			if ((*b)->x < (*b)->next->x)
				sb(*b);
			pa(a, b);
			pa(a, b);
		}
		else
		{
			pa(a, b);
			if ((*b)->x < (*b)->next->x)
				sb(*b);
			pa(a, b);
			pa(a, b);
		}
	}
	p_to_null(*a);
	return (0);
}
