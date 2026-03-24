/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_complex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:10 by leon              #+#    #+#             */
/*   Updated: 2026/03/24 10:34:04 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	loop_a_to_b(x_list **a, x_list **b)
{
	while (!check_sorted(*a))
	{
		if ((*a)->p >= get_last_p(*a))
		{
			if (!a_to_b(a, b))
				return (0);
		}
		else
		{
			if (!a_to_b_rev(a, b))
				return (0);
		}
	}
	return (0);
}

int	loop(x_list **a, x_list **b)
{
	int	k;
	int	progressed;

	progressed = 1;
	while (progressed == 1)
	{
		progressed = 0;
		if (!check_sorted(*a))
		{
			loop_a_to_b(a, b);
			progressed = 1;
		}
		else
			p_to_null(*a);
		if (!(*b))
			return (0);
		if ((*b)->x > get_last(*b))
		{
			k = b_to_a(a, b);
			progressed = 1;
			if (!k)
				return (0);
			if (!(*b))
				return (0);
			if (k == 2)
				continue ;
		}
		if ((*b)->x < get_last(*b) && check_sorted(*a))
		{
			if (!b_to_a_rev(a, b))
				return (0);
			progressed = 1;
		}
	}
	return (0);
}

int	algorithm_complex(x_list **a, x_list **b)
{
	int	i;

	i = 1;
	while (i)
		i = a_to_b(a, b);
	loop(a, b);
	return (0);
}
