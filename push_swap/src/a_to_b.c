/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:09 by leon              #+#    #+#             */
/*   Updated: 2026/03/23 18:07:25 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	a_to_b2(x_list **a, x_list **b, int p, int k)
{
	int	m;
	int	i;
	int ra_count;

	m = find_median(*a);
	i = 0;
	ra_count = 0;
	while (i < k)
	{
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = p;
		}
		else
		{
			ra(a);
			ra_count++;
		}
		i++;
	}
	while (ra_count-- > 0)
		rra(a);
	return (0);
}

int	a_to_b(x_list **a, x_list **b)
{
	int	k;
	int	p;

	if ((*a)->opts->debug)
		printlists(*a, *b);
	if (!(*b))
		p = 1;
	else
		p = (*b)->p + 1;
	k = get_size(*a);
	if (k <= 3)
	{
		sort3_a(a, b, k);
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
	int restore_ra;

	m = find_median_end(*a);
	i = 0;
	restore_ra = 0;
	while (i < k)
	{
		rra(a);
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = p;
		}
		else
			restore_ra++;
		i++;
	}
	while (restore_ra-- > 0)
		ra(a);
	return (0);
}

int	a_to_b_rev(x_list **a, x_list **b)
{
	int	k;
	int	p;

	if ((*a)->opts->debug)
		printlists(*a, *b);
	if (!(*a) || sorted(*a))
		return (0);
	p = (*b)->p + 1;
	k = get_size_end(*a);
	if (k <= 3)
	{
		p = k;
		while (p-- > 0)
			rra(a);
		sort3_a(a, b, k);
		return (0);
	}
	a_to_b_rev2(a, b, p, k);
	if (sorted(*a))
		return (0);
	return (1);
}
