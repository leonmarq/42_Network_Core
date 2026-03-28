/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3_b_pa_rev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:09:53 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/25 13:54:25 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	sort2_b_pa_rev(t_slist **a, t_slist **b)
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

static
int	biggest_top_bottom_switch(t_slist **a, t_slist **b)
{
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
	return (0);
}

static
int	case_1n2(t_slist **a, t_slist **b)
{
	int	k;

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
	return (0);
}

static
int	case_step2_rrb(t_slist **a, t_slist **b)
{
	rrb(b);
	if (get_biggest(*b) == (*b)->x)
	{
		pa(a, b);
		biggest_top_bottom_switch(a, b);
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
	return (0);
}

int	sort3_b_pa_rev(t_slist **a, t_slist **b)
{
	if (get_size_end_p(*b) == 2)
		return (case_1n2(a, b));
	else
	{
		rrb(b);
		if (get_biggest(*b) == (*b)->x)
		{
			pa(a, b);
			rrb(b);
			biggest_top_bottom_switch(a, b);
		}
		else
		{
			case_step2_rrb(a, b);
		}
		pa(a, b);
	}
	return (0);
}
