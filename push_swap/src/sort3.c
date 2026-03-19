/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:31 by leon              #+#    #+#             */
/*   Updated: 2026/03/19 13:22:19 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort3(x_list **a, x_list **b, int k)
{
	if (k == 2)
	{
		if ((*a)->x > (*a)->next->x)
			sa(*a);
		return (0);
	}
	else if (k == 3)
	{
		if ((*a)->x > (*a)->next->x && (*a)->x > (*a)->next->next->x)
			sa(*a);
		if ((*a)->next->x > (*a)->next->next->x && (*a)->x < (*a)->next->x)
		{
			pb(a, b);
			sa(*a);
			pa(a, b);
		}
		if ((*a)->x > (*a)->next->x)
			sa(*a);
	}
	p_to_null(*a);
	return (0);
}

int	sort3_b_pa(x_list **a, x_list **b, int k)
{
	if (k == 2)
	{
		if ((*b)->x < (*b)->next->x)
			sb(*b);
	}
	else if (k == 3)
	{
		if ((*b)->x < (*b)->next->x && (*b)->x < (*b)->next->next->x)
			sb(*b);
		if ((*b)->next->x < (*b)->next->next->x && (*b)->x > (*b)->next->x)
		{
			pa(a, b);
			sb(*b);
			pb(a, b);
		}
		if ((*b)->x < (*b)->next->x)
			sb(*b);
	}
	while (k > 0)
	{
		pa(a, b);
		k--;
	}
	p_to_null(*a);
	return (0);
}
