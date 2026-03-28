/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:17:02 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 16:48:37 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_slist	*get_lowest(t_slist *t)
{
	t_slist	*lowest;

	lowest = t;
	while (t)
	{
		if (t->x < lowest->x)
			lowest = t;
		t = t->next;
	}
	return (lowest);
}

int	algorithm_simple(t_slist **a, t_slist **b)
{
	t_slist	*lowest;
	t_opts	*opts;

	opts = (*a)->opts;
	lowest = get_lowest(*a);
	while (*a)
	{
		if (opts->debug)
			printlists(*a,*b);
		while (*a != lowest)
			ra(a);
		pb(a, b);
		if (!(*a))
			break ;
		lowest = find_next_lowest(*a, lowest);
	}
	while (*b)
		pa(a, b);
	return (0);
}
