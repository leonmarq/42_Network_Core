/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:12:08 by leonmarq          #+#    #+#             */
/*   Updated: 2026/07/01 09:08:51 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	enter_waiting(t_coder *p, struct timeval ts)
{
	p->arrival_order = p->shared->dongle_center.ticket;
	p->shared->dongle_center.ticket = p->shared->dongle_center.ticket + 1;
	if (p->shared->dongle_center.scheduler == FIFO)
		p->prio = p->arrival_order;
	else
		p->prio = time_to_long(ts);
	p->state = CODER_REQUEST;
	return (0);
}

int	scheduled_best_option(t_coder *p)
{
	if (!both_dongles_available(p))
		return (0);
	if (p->lefty->state == CODER_REQUEST && p->lefty->prio < p->prio)
		return (0);
	if (p->righty->state == CODER_REQUEST && p->righty->prio < p->prio)
		return (0);
	return (1);
}
