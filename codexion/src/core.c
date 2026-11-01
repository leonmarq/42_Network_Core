/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 15:51:16 by leonmarq          #+#    #+#             */
/*   Updated: 2026/07/01 10:39:31 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	acquire_dongles(t_coder *p)
{
	t_dongle_center	*dc;
	int				fail;
	struct timeval	ts_last_cp;

	fail = 0;
	dc = &p->shared->dongle_center;
	pthread_mutex_lock(&p->shared->dead_mutex);
	ts_last_cp = p->ts_last_cp;
	pthread_mutex_unlock(&p->shared->dead_mutex);
	pthread_mutex_lock(&dc->mutex);
	enter_waiting(p, ts_last_cp);
	while (!dc->stopping && !scheduled_best_option(p))
		pthread_cond_wait(&dc->changed_cond, &dc->mutex);
	if (dc->stopping)
	{
		pthread_mutex_unlock(&dc->mutex);
		return (1);
	}
	update_states(p, D_USED);
	pthread_cond_broadcast(&dc->changed_cond);
	pthread_mutex_unlock(&dc->mutex);
	if (check_if_dead(p))
		fail = 1;
	return (fail);
}

int	coder_compile(t_coder *p)
{
	if (acquire_dongles(p))
		return (1);
	pthread_mutex_lock(&p->shared->dead_mutex);
	gettimeofday(&p->ts_last_cp, NULL);
	pthread_mutex_unlock(&p->shared->dead_mutex);
	m_printf_func(p, CODER_TAKES);
	m_printf_func(p, CODER_TAKES);
	m_printf_func(p, CODER_COMPILE);
	usleep(p->compile);
	pthread_mutex_lock(&p->shared->dongle_center.mutex);
	update_states(p, D_FREE);
	pthread_cond_broadcast(&p->shared->dongle_center.changed_cond);
	pthread_mutex_unlock(&p->shared->dongle_center.mutex);
	p->i_loop = p->i_loop + 1;
	if (check_if_dead(p))
		return (1);
	return (0);
}

int	life_loop(t_coder *p)
{
	while (p->i_loop < p->loops)
	{
		if (coder_compile(p))
			return (1);
		if (!(p->i_loop < p->loops))
			break ;
		if (check_if_dead(p))
			return (1);
		m_printf_func(p, CODER_DEBUG);
		usleep(p->debug);
		if (check_if_dead(p))
			return (1);
		m_printf_func(p, CODER_REFACTOR);
		usleep(p->refactor);
		if (check_if_dead(p))
			return (1);
	}
	pthread_mutex_lock(&p->shared->dead_mutex);
	p->done = 1;
	pthread_mutex_unlock(&p->shared->dead_mutex);
	m_printf_func(p, CODER_COMPLETED);
	return (0);
}

void	*life(void *p_v)
{
	t_coder	*p;

	p = (t_coder *)p_v;
	life_loop(p);
	return ((void *)&(p->id));
}
