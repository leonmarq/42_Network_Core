/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:17:10 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/24 20:17:11 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	printlists(x_list *a, x_list *b)
{
	write(1, "a:\n", 3);
	while (a)
	{
		ft_putnbr_fd(a->x, 1);
		write (1, " ", 1);
		ft_putnbr_fd(a->p, 1);
		a = a->next;
		write(1, "\n", 1);
	}
	write(1, "\nb:\n", 4);
	while (b)
	{
		ft_putnbr_fd(b->x, 1);
		write (1, " ", 1);
		ft_putnbr_fd(b->p, 1);
		b = b->next;
		write(1, "\n", 1);
	}
	return (1);
}
