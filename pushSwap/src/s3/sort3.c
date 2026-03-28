/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:31 by leon              #+#    #+#             */
/*   Updated: 2026/03/25 13:54:40 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	sort3_a(t_slist **a, t_slist **b, int k)
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
	if (check_sorted(*a) == 1)
		p_to_null(*a);
	return (0);
}
