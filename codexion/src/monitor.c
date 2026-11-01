/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:19:19 by leonmarq          #+#    #+#             */
/*   Updated: 2026/07/01 09:01:51 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*coder_dead(t_data *data)
{
	int				i;
	struct timeval	ts;
	t_coder			*dead_coder;
	t_coder			*coders;

	i = 0;
	dead_coder = 0;
	coders = data->coders;
	gettimeofday(&ts, NULL);
	while (i < data->n_of_p)
	{
		if (!coders[i].done && time_diff(coders[i].ts_last_cp,
				ts) >= coders[i].death)
		{
			coders[i].dead = 1;
			coders->shared->coder_down = 1;
			dead_coder = &coders[i];
			break ;
		}
		i++;
	}
	return (dead_coder);
}

int	conditional_dongle_wakeup(t_data *data)
{
	int				i;
	t_dongle_center	*dc;
	struct timeval	ts;
	long long		time_since_release;

	i = 0;
	dc = &data->shared.dongle_center;
	pthread_mutex_lock(&dc->mutex);
	while (i < dc->count)
	{
		ts = data->coders[i].dongle_left->time_released;
		time_since_release = time_ms(ts);
		if (time_since_release > dc->cooldown
			&& time_since_release < dc->cooldown + 20)
			pthread_cond_broadcast(&dc->changed_cond);
		i++;
	}
	pthread_mutex_unlock(&dc->mutex);
	return (0);
}

int	broadcast_stop(t_dongle_center *dc)
{
	int	i;

	pthread_mutex_lock(&dc->mutex);
	dc->stopping = 1;
	i = pthread_cond_broadcast(&dc->changed_cond);
	pthread_mutex_unlock(&dc->mutex);
	return (i);
}

void	*monitor(void *arg)
{
	t_data	*data;
	t_coder	*dead_coder;
	int		stop;

	data = (t_data *)arg;
	dead_coder = 0;
	stop = 0;
	while (!stop)
	{
		pthread_mutex_lock(&data->shared.dead_mutex);
		dead_coder = coder_dead(data);
		if (all_coders_down(data))
			stop = 1;
		pthread_mutex_unlock(&data->shared.dead_mutex);
		conditional_dongle_wakeup(data);
		if (dead_coder)
		{
			m_printf_func(dead_coder, CODER_BURNOUT);
			broadcast_stop(&data->shared.dongle_center);
			stop = 1;
		}
		usleep(9000);
	}
	return ((void *)0);
}
