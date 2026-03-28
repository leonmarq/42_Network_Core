/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_complex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:10 by leon              #+#    #+#             */
/*   Updated: 2026/03/25 15:38:34 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static
int	loop_a_to_b(t_slist **a, t_slist **b)
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

static
int	b_to_a_manager(t_slist **a, t_slist **b)
{
	int	did_something;

	did_something = 0;
	if ((*b)->p >= get_last_p(*b))
	{
		b_to_a(a, b);
		did_something = 1;
	}
	else if ((*b)->p < get_last_p(*b))
	{
		b_to_a_rev(a, b);
		did_something = 1;
	}
	return (did_something);
}

static
int	loop(t_slist **a, t_slist **b)
{
	int	progressed;

	progressed = 1;
	while (progressed)
	{
		if ((*a)->opts->debug)
			printlists(*a, *b);
		progressed = 0;
		if (!check_sorted(*a))
		{
			loop_a_to_b(a, b);
			progressed = 1;
		}
		p_to_null(*a);
		if (!(*b))
			continue ;
		if ((*a)->opts->debug)
			printlists(*a, *b);
		if (b_to_a_manager(a, b))
			progressed = 1;
	}
	return (0);
}

int	algorithm_complex(t_slist **a, t_slist **b)
{
	return (loop(a, b));
}
