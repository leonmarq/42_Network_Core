/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:27 by leon              #+#    #+#             */
/*   Updated: 2026/03/26 16:13:38 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	p_to_null(t_slist *a)
{
	while (a)
	{
		a->p = 0;
		a = a->next;
	}
	return (0);
}

int	check_sorted(t_slist *a)
{
	if (!a)
		return (1);
	if (!(a->next))
		return (1);
	while (a->next)
	{
		if (a->x > a->next->x)
			return (0);
		a = a->next;
	}
	return (1);
}

t_slist	*find_next_lowest(t_slist *stack, t_slist *current)
{
	t_slist	*compare;
	t_slist	*lowest_element;
	int		lowest_x;

	compare = stack;
	lowest_x = get_biggest(stack);
	lowest_element = NULL;
	while (compare)
	{
		if (compare->x > current->x)
		{
			if (compare->x < lowest_x || lowest_element == NULL)
			{
				lowest_x = compare->x;
				lowest_element = compare;
			}
		}
		compare = compare->next;
	}
	return (lowest_element);
}
