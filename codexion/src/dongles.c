/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 17:48:50 by leonmarq          #+#    #+#             */
/*   Updated: 2026/07/01 08:59:39 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	update_states(t_coder *p, t_dongle_state state)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	p->dongle_left->state = state;
	p->dongle_right->state = state;
	if (state == D_FREE)
	{
		p->dongle_left->time_released = now;
		p->dongle_right->time_released = now;
		p->state = CODER_DEBUG;
	}
	else
		p->state = CODER_COMPILE;
	return (0);
}

int	both_dongles_available(t_coder *p)
{
	t_dongle	*left;
	t_dongle	*right;
	long long	cooldown;

	left = p->dongle_left;
	right = p->dongle_right;
	cooldown = p->shared->dongle_center.cooldown;
	if (!(left->state == D_FREE && p->dongle_right->state == D_FREE))
		return (0);
	if (left == right)
		return (0);
	if (time_ms(left->time_released) < cooldown)
		return (0);
	if (time_ms(right->time_released) < cooldown)
		return (0);
	return (1);
}
