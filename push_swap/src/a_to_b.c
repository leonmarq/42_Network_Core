/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:09 by leon              #+#    #+#             */
/*   Updated: 2026/03/23 12:10:25 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	a_to_b2(x_list **a, x_list **b, int p, int k)
{
	int	m;
	int	i;
	int ra_count;
	int rb_count;

	m = find_median(*a);
	i = 0;
	ra_count = 0;
	rb_count = 0;
	while (i < k)
	{
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = p;
			if ((*b)->x == m)
			{
				rb(b);
				rb_count++;
			}
		}
		else
		{
			ra(a);
			ra_count++;
		}
		i++;
	}
	while (rb_count-- > 0 && ra_count-- > 0)
		rrr(a, b);
	while (ra_count-- > 0)
		rra(a);
	while (rb_count-- > 0)
		rrb(b);
	return (0);
}

int	a_to_b(x_list **a, x_list **b)
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
int	a_to_b_rev2(x_list **a, x_list **b, int p, int k)
{
	int	m;
	int	i;
	int rra_count;
	int rb_count;

	rra_count = 0;
	rb_count = 0;
	m = find_median_end(*a);
	i = 0;
	while (i < k)
	{
		rra(a);
		rra_count++;
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = p;
			if ((*b)->x == m)
			{
				rb(b);
				rb_count++;
			}
		}
		i++;
	}
	while (rra_count-- > 0)
		rra(a);
	while (rb_count-- > 0)
		rrb(b);
	return (0);
}

int	a_to_b_rev(x_list **a, x_list **b)
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
