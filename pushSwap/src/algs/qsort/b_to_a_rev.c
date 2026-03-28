/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:08:07 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 14:27:09 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static
int	b_to_a_rev2(t_slist **a, t_slist **b)
{
	int	m;
	int	k;
	int	p;

	k = get_size_end_p(*b);
	p = (*a)->p + 1;
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

int	b_to_a_rev(t_slist **a, t_slist **b)
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
