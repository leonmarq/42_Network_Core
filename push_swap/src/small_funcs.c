/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:27 by leon              #+#    #+#             */
/*   Updated: 2026/03/25 13:31:04 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
