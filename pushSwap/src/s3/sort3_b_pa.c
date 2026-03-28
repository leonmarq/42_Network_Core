/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3_b_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:32:14 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/25 13:54:33 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static
int	sort2_b_pa(t_slist **a, t_slist **b)
{
	if ((*b)->x < (*b)->next->x)
		sb(*b);
	pa(a, b);
	pa(a, b);
	return (0);
}

static
int	case_biggest_third(t_slist **a, t_slist **b)
{
	rb(b);
	sb(*b);
	pa(a, b);
	if ((*b)->x < get_last(*b))
	{
		rrb(b);
		pa(a, b);
	}
	else
	{
		pa(a, b);
		rrb(b);
	}
	pa(a, b);
	return (0);
}

static
int	case_biggest_second(t_slist **a, t_slist **b)
{
	if ((*b)->x < (*b)->next->x)
		sb(*b);
	pa(a, b);
	if ((*b)->x < (*b)->next->x)
		sb(*b);
	pa(a, b);
	pa(a, b);
	return (0);
}

int	sort3_b_pa(t_slist **a, t_slist **b, int k)
{
	t_slist	*t;

	if (k <= 2)
		return (sort2_b_pa(a, b));
	else if (k == 3)
	{
		t = *b;
		if (t->next->next-> x > t->x && t->next->next->x > t->next->x)
			case_biggest_third(a, b);
		else if (t->next->x > t->x && t->next->x > t->next->next->x)
			case_biggest_second(a, b);
		else
		{
			pa(a, b);
			if (t->x < t->next->x)
				sb(*b);
			pa(a, b);
			pa(a, b);
		}
	}
	p_to_null(*a);
	return (0);
}
