/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 15:50:57 by leonmarq          #+#    #+#             */
/*   Updated: 2026/07/01 10:50:54 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	destroy_all_pthread(t_data *data)
{
	pthread_mutex_destroy(&data->shared.dongle_center.mutex);
	pthread_cond_destroy(&data->shared.dongle_center.changed_cond);
	pthread_mutex_destroy(&data->shared.dead_mutex);
	pthread_mutex_destroy(&data->shared.print_mutex);
	return (0);
}

int	cleanup_below(t_data *data, int i)
{
	i--;
	destroy_all_pthread(data);
	while (i >= 0)
		free(data->coders[i--].dongle_left);
	free(data->coders);
	return (0);
}

int	join_every_other(t_coder *coders, int i)
{
	while (i >= 0)
	{
		pthread_join(coders[i].thread, NULL);
		i = i - 2;
	}
	return (0);
}

int	cleanup_failed_thread(t_data *data, int i)
{
	int	x;

	pthread_mutex_lock(&data->shared.dongle_center.mutex);
	data->shared.dongle_center.stopping = 1;
	pthread_cond_broadcast(&data->shared.dongle_center.changed_cond);
	pthread_mutex_unlock(&data->shared.dongle_center.mutex);
	i -= 2;
	if (i % 2)
	{
		x = data->n_of_p - 1;
		if (x % 2)
			x--;
	}
	else
		x = i;
	join_every_other(data->coders, x);
	if (i % 2)
		join_every_other(data->coders, i);
	cleanup_below(data, data->n_of_p);
	return (0);
}

int	cleanup(t_data *data)
{
	long long	i;
	void		*t_res;

	i = 0;
	while (i < data->n_of_p)
	{
		pthread_join(data->coders[i].thread, &t_res);
		i++;
	}
	pthread_mutex_destroy(&data->shared.dongle_center.mutex);
	pthread_cond_destroy(&data->shared.dongle_center.changed_cond);
	pthread_mutex_destroy(&data->shared.dead_mutex);
	pthread_mutex_destroy(&data->shared.print_mutex);
	i = 0;
	while (i < data->n_of_p)
		free(data->coders[i++].dongle_left);
	free(data->coders);
	return (0);
}
