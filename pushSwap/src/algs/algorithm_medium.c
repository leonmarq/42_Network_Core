/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_medium.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:16:39 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 16:47:35 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	set_lowest(t_slist **a, t_slist **b)
{
	int	p;

	p = (*b)->p;
	while (!*a && *b && (*b)->p == p)
	{
		if ((*b)->x == get_size(*b) - 1)
			pa(a, b);
		else
			rb(b);
	}
	return ((*b)->x);
}

int	algorithm_medium(t_slist **a, t_slist **b)
{
	t_chunk	chunk;

	if (!*a || *b)
		return (1);
	assign_ranks_to_p(*a);
	p_to_x(a);
	chunk = gen_chunks(a);
	sort_by_chunk(a, b, chunk);
	set_lowest(a, b);
	sort_loop(a, b);
	return (0);
}
