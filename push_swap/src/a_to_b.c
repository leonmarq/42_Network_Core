/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:09 by leon              #+#    #+#             */
/*   Updated: 2026/03/24 17:51:51 by leonmarq         ###   ########.fr       */
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
		new_p = get_biggest_p(*b) + 1;
	m = find_median(*a);
	i = 0;
	k = get_size_p(*a);
	while (i < k)
	{
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = new_p;
			if ((*b)->x == m)
				rb(b);
		}
		else
			ra(a);

		i++;
	}
	if (get_last(*b) == m)
		rrb(b);
	return (0);
}

int	a_to_b(x_list **a, x_list **b)
{
	int	k;

	k = get_size_p(*a);
	if (k <= 3)
	{
		sort3_a(a, b, k);
		return (0);
	}
	else
		a_to_b2(a, b);
	if (check_sorted(*a))
		return (p_to_null(*a));
	return (1);
}

static
int	a_to_b_rev2(x_list **a, x_list **b)
{
	int	m;
	int	i;
	int	new_p;
	int	k;

	new_p = get_biggest_p(*b) + 1;
	k = get_size_end_p(*a);
	m = find_median_end(*a);
	i = 0;
	while (i < k)
	{
		rra(a);
		if ((*a)->x <= m)
		{
			pb(a, b);
			(*b)->p = new_p;
			if ((*b)->x == m)
				rb(b);
		}
		i++;
	}
	if (get_last(*b) == m)
		rrb(b);
	return (0);
}

int	sort3_a_rev(x_list **a, x_list **b, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		rra(a);
		i++;
	}
	return sort3_a(a, b, k);
}

int	a_to_b_rev(x_list **a, x_list **b)
{
	int	k;

	if (!(*a) || check_sorted(*a))
		return (0);
	k = get_size_end_p(*a);
	if (k <= 3)
		sort3_a_rev(a, b, k);
	else
		a_to_b_rev2(a, b);
	if (check_sorted(*a))
		return (p_to_null(*a));
	return (1);
}
