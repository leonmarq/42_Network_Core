/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:09 by leon              #+#    #+#             */
/*   Updated: 2026/03/24 10:36:02 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	a_to_b2(x_list **a, x_list **b)
{
	int	m;
	int	i;
	int	k;
	int	new_p;

	if (!(*b))
		new_p = 1;
	else
		new_p = (*b)->p + 1;
	m = find_median(*a);
	i = 0;
	k = get_size_p(*a);
	while (i < k)
	{
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = new_p;
		}
		else
			ra(a);
		i++;
	}
	return (0);
}

int	a_to_b(x_list **a, x_list **b)
{
	int	k;

	if ((*a)->opts->debug)
		printlists(*a, *b);

	k = get_size_p(*a);
	if (k <= 3)
	{
		sort3_a(a, b, k);
		return (0);
	}
	else
		a_to_b2(a, b);
	if (check_sorted(*a))
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

	if (!(*a) || check_sorted(*a))
		return (0);
	p = (*b)->p + 1;
	k = get_size_end_p(*a);
	if (k <= 3)
	{
		p = k;
		while (p-- > 0)
			rra(a);
		sort3_a(a, b, k);
		return (0);
	}
	a_to_b_rev2(a, b, p, k);
	if (check_sorted(*a))
		return (0);
	return (1);
}
