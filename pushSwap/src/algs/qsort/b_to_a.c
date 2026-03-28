/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:13 by leon              #+#    #+#             */
/*   Updated: 2026/03/26 14:27:10 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static
int	b_to_a2(t_slist **a, t_slist **b, int amount)
{
	int	m;
	int	new_p;

	new_p = get_biggest_p(*a) + 1;
	m = find_median(*b);
	while (amount > 0)
	{
		if ((*b)->x >= m)
		{
			pa(a, b);
			(*a)->p = new_p;
			if ((*a)->x == m && (*a)->x > get_last(*a))
				ra(a);
		}
		else
			rb(b);
		amount--;
	}
	while (get_last_p(*a) != 0)
		rra(a);
	return (0);
}

int	b_to_a(t_slist **a, t_slist **b)
{
	int	amount;

	if (!(*b))
		return (0);
	while ((*b)->x == get_biggest(*b))
	{
		pa(a, b);
		if (check_sorted(*a))
			p_to_null(*a);
		if (!(*b))
			return (0);
		if (get_biggest_p(*b) != (*b)->p)
			return (2);
	}
	amount = get_size_p(*b);
	if (amount <= 3)
	{
		sort3_b_pa(a, b, amount);
		return (2);
	}
	else
		b_to_a2(a, b, amount);
	return (1);
}
