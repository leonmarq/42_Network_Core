/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:54:17 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/27 14:42:56 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	set_strat(char *s, int *strat)
{
	if (ft_strncmp("--simple", s, 15) == 0)
		*strat = (SIMPLE);
	else if (ft_strncmp("--medium", s, 15) == 0)
		*strat = (MEDIUM);
	else if (ft_strncmp("--complex", s, 15) == 0)
		*strat = (COMPLEX);
	else if (ft_strncmp("--adaptive", s, 15) == 0)
		*strat = (ADAPTIVE);
	else
		return (0);
	return (1);
}
