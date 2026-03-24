/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:13 by leon              #+#    #+#             */
/*   Updated: 2026/03/24 16:14:25 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static
int	b_to_a2(x_list **a, x_list **b, int p, int k)
{
	int	m;

	m = find_median(*b);
	while (k > 0)
	{
		if ((*b)->x >= m)
		{
			pa(a, b);
			(*a)->p = p;
			if ((*a)->x == m && (*a)->x > get_last(*a))
				ra(a);
		}
		else
			rb(b);
		k--;
	}
	while (get_last_p(*a) != 0)
		rra(a);
	return (0);
}

int	b_to_a(x_list **a, x_list **b)
{
	int	k;
	int	p;

	if (!(*b))
		return (0);
	k = get_size_p(*b);
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
int	b_to_a_rev2(x_list **a, x_list **b)
{
	int	m;
	int did_ra;
	int k;
	int p;

	k = get_size_end_p(*b);
	p = (*a)->p + 1;
	m = find_median_end(*b);
	did_ra = 0;
	while (k > 0)
	{
		rrb(b);
		if ((*b)->x >= m)
		{
			pa(a, b);
			(*a)->p = p;
			if ((*a)->x == m)
			{
				ra(a);
				did_ra = 1;
			}
		}
		k--;
	}
	if (did_ra)
		rra(a);
	return (0);
}

int sort2_b_pa_rev(x_list **a, x_list **b)
{
	rrb(b);
	if ((*b)->x > get_last(*b))
	{
		pa(a, b);
		rrb(b);
		pa(a, b);
	}
	else
	{
		rrb(b);
		pa(a, b);
		pa(a, b);
	}
	return (0);
}

int	sort3_b_pa_rev(x_list **a, x_list **b)
{
	int k;

	k = get_size_end_p(*b);
	if (!k)
		return (0);
	if (k == 1)
	{
		rrb(b);
		pa(a, b);
	}
	else if (k == 2)
		sort2_b_pa_rev(a, b);
	else
	{
		rrb(b);
		if (get_biggest(*b) == (*b)->x)
		{
			pa(a, b);
			rrb(b);
			if (get_biggest(*b) == (*b)->x)
			{
				pa(a, b);
				rrb(b);
			}
			else
			{
				rrb(b);
				pa(a, b);
			}
		}
		else
		{
			rrb(b);
			if (get_biggest(*b) == (*b)->x)
			{
				pa(a, b);
				if (get_biggest(*b) == (*b)->x)
				{
					pa(a, b);
					rrb(b);
				}
				else
				{
					rrb(b);
					pa(a, b);
				}
			}
			else
			{
				rrb(b);
				pa(a, b);
				if ((*b)->x > (*b)->next->x)
					pa(a, b);
				else
				{
					sb(*b);
					pa(a, b);
				}
			}
		}
		pa(a, b);
	}
	return (0);
}

int	b_to_a_rev(x_list **a, x_list **b)
{

	if (!(*b))
		return (0);
	if (get_size_end_p(*b) <= 3)
		sort3_b_pa_rev(a, b);
	else
		b_to_a_rev2(a, b);
	if (check_sorted(*a))
		return (p_to_null(*a));
	return (1);
}
