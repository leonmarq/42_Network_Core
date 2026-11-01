/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:40:31 by leon              #+#    #+#             */
/*   Updated: 2026/07/01 10:50:44 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	thread_create_loop(t_data *data, long long start)
{
	int	err;

	while (start < data->n_of_p)
	{
		pthread_mutex_lock(&data->shared.dead_mutex);
		gettimeofday(&data->coders[start].ts_last_cp, NULL);
		pthread_mutex_unlock(&data->shared.dead_mutex);
		err = pthread_create(&data->coders[start].thread, NULL, life,
				&data->coders[start]);
		if (err)
		{
			printf("error creating thread %lld\n", start);
			return (start + 1);
		}
		start += 2;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		err;

	if (init_data(argv, &data, argc))
		return (1);
	err = thread_create_loop(&data, 0);
	if (err)
		return (cleanup_failed_thread(&data, err - 1) + 1);
	usleep(2500);
	err = thread_create_loop(&data, 1);
	if (err)
		return (cleanup_failed_thread(&data, err - 1) + 1);
	if (pthread_create(&data.monitor, NULL, monitor, &data))
	{
		broadcast_stop(&data.shared.dongle_center);
		return (cleanup(&data) + 1);
	}
	pthread_join(data.monitor, NULL);
	cleanup(&data);
	return (0);
}
