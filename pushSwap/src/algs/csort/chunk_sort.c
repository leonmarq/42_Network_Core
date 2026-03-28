/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:48:49 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 17:16:33 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

t_chunk	gen_chunks(t_slist **a)
{
	t_chunk	chunk;
	t_slist	*current;
	int		size;

	size = get_size(*a);
	chunk.count = fsqurt(size);
	if (chunk.count == 0)
		chunk.count = 1;
	chunk.size = (size + chunk.count - 1) / chunk.count;
	current = *a;
	while (current)
	{
		current->p = current->x / chunk.size;
		current = current->next;
	}
	return (chunk);
}

static
int	rotate_and_pb(t_slist **a, t_slist **b, int chunk)
{
	int	els_pushed;

	els_pushed = 0;
	if (top_chunk_closer(*a, chunk))
	{
		while ((*a)->p != chunk)
			ra(a);
		pb(a, b);
		els_pushed++;
	}
	else
	{
		while ((*a)->p != chunk)
			rra(a);
		pb(a, b);
		els_pushed++;
	}
	return (els_pushed);
}

static
int	rotate_and_pa(t_slist **a, t_slist **b, t_slist *el, int v)
{
	if (top_value_closer(*b, v))
	{
		while ((*b)->x != el->x)
			rb(b);
		pa(a, b);
	}
	else
	{
		while ((*b)->x != el->x)
			rrb(b);
		pa(a, b);
	}
	return (0);
}

int	sort_by_chunk(t_slist **a, t_slist **b, t_chunk chunk)
{
	int	cur_chunk;
	int	els_pushed;

	cur_chunk = 0;
	els_pushed = 0;
	while ((*a) && cur_chunk < chunk.count)
	{
		els_pushed += rotate_and_pb(a, b, cur_chunk);
		if (els_pushed == chunk.size)
		{
			cur_chunk++;
			els_pushed = 0;
			if (cur_chunk >= chunk.count)
				return (1);
		}
	}
	return (0);
}

int	sort_loop(t_slist **a, t_slist **b)
{
	int		cur_chunk;
	t_slist	*to_be_pushed;
	int		next_highest;

	while (*b)
	{
		cur_chunk = (*b)->p;
		while (*b && ((*b)->p == cur_chunk || get_last_p(*b) == cur_chunk))
		{
			next_highest = (*a)->x - 1;
			to_be_pushed = get_by_x(*b, next_highest);
			rotate_and_pa(a, b, to_be_pushed, next_highest);
		}
	}
	return (0);
}
