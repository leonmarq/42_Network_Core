/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:21:06 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 17:21:07 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_slist	*get_by_x(t_slist *stack, int x)
{
	while (stack)
	{
		if (stack->x == x)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}
