/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:09 by leon              #+#    #+#             */
/*   Updated: 2022/04/08 15:36:11 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	a_to_b2(t_list **a, t_list **b, int p, int k)
{
	int	m;
	int	i;

	m = find_median(*a);
	i = 0;
	while (i < k)
	{
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = p;
			if ((*b)->x == m)
				rb(b);
		}
		else
			ra(a);
		i++;
	}
	rrb(b);
	return (0);
}

int	a_to_b(t_list **a, t_list **b)
{
	int	k;
	int	p;

	if (!(*b))
		p = 1;
	else
		p = (*b)->p + 1;
	k = get_size(*a);
	if (k <= 3)
	{
		sort3(a, b, k);
		return (0);
	}
	a_to_b2(a, b, p, k);
	if (sorted(*a))
		return (0);
	return (1);
}

static
int	a_to_b_rev2(t_list **a, t_list **b, int p, int k)
{
	int	m;
	int	i;

	m = find_median_end(*a);
	i = 0;
	while (i < k)
	{
		rra(a);
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = p;
			if ((*b)->x == m)
				rb(b);
		}
		i++;
	}
	rrb(b);
	return (0);
}

int	a_to_b_rev(t_list **a, t_list **b)
{
	int	k;
	int	p;

	p = (*b)->p + 1;
	k = get_size_end(*a);
	if (k <= 3)
	{
		p = k;
		while (p-- > 0)
			rra(a);
		sort3(a, b, k);
		return (0);
	}
	a_to_b_rev2(a, b, p, k);
	if (sorted(*a))
		return (0);
	return (1);
}
