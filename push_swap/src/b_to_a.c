/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:13 by leon              #+#    #+#             */
/*   Updated: 2022/04/08 15:36:16 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	b_to_a2(t_list **a, t_list **b, int p, int k)
{
	int	m;

	m = find_median(*b);
	while (k > 0)
	{
		if ((*b)->x >= m)
		{
			pa(a, b);
			(*a)->p = p;
			if ((*a)->x == m)
				ra(a);
		}
		else
			rb(b);
		k--;
	}
	rra(a);
	return (0);
}

int	b_to_a(t_list **a, t_list **b)
{
	int	k;
	int	p;

	if ((*b)->x == get_biggest(*b))
		pa(a, b);
	if (!(*b))
		return (0);
	k = get_size(*b);
	p = (*a)->p + 1;
	if (k <= 3)
	{
		sort3_b_pa(a, b, k);
		return (2);
	}
	else
		b_to_a2(a, b, p, k);
	return (1);
}

static
int	b_to_a_rev2(t_list **a, t_list **b, int p, int k)
{
	int	m;

	m = find_median_end(*b);
	while (k > 0)
	{
		rrb(b);
		if ((*b)->x >= m)
		{
			pa(a, b);
			(*a)->p = p;
			if ((*a)->x == m)
				ra(a);
		}
		k--;
	}
	rra(a);
	return (0);
}

int	b_to_a_rev(t_list **a, t_list **b)
{
	int	k;
	int	m;
	int	p;

	k = get_size_end(*b);
	p = (*a)->p + 1;
	m = k;
	if (k <= 3)
	{
		while (m-- > 0)
			rrb(b);
		sort3_b_pa(a, b, k);
	}
	else
		b_to_a_rev2(a, b, p, k);
	return (1);
}
