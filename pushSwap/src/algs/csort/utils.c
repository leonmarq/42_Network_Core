/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:43:56 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 17:20:57 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	top_value_closer(t_slist *b, int value)
{
	int		i;
	t_slist	*current;

	current = b;
	i = 0;
	while (current && current->x != value)
	{
		i++;
		current = current->next;
	}
	if (i >= get_size(b) - i)
		return (0);
	else
		return (1);
}

int	top_chunk_closer(t_slist *a, int chunk)
{
	int		i_current;
	int		i_top;
	int		i_bottom;
	t_slist	*current;

	current = a;
	i_top = -1;
	i_bottom = 0;
	i_current = 0;
	while (current)
	{
		if (current->p == chunk && i_top == -1)
		{
			i_top = i_current;
		}
		else if (current->p == chunk && i_top != -1)
			i_bottom = i_current;
		i_current++;
		current = current->next;
	}
	if (i_top <= (i_current - i_bottom))
		return (1);
	else
		return (0);
}

int	assign_ranks_to_p(t_slist *stack)
{
	t_slist	*current;
	t_slist	*compare;
	int		rank;

	current = stack;
	rank = 0;
	compare = stack;
	while (compare)
	{
		if (compare->x < current->x)
			current = compare;
		compare = compare->next;
	}
	current->p = rank;
	rank++;
	compare = stack;
	while (rank < get_size(stack))
	{
		current = find_next_lowest(stack, current);
		if (!current)
			return (1);
		current->p = rank;
		rank++;
	}
	return (0);
}
