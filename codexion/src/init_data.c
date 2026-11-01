/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:14:39 by leon              #+#    #+#             */
/*   Updated: 2026/07/01 08:15:28 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_coder(t_coder *p, int i, t_data *data)
{
	p->id = i + 1;
	p->dongle_left = ft_calloc(1, sizeof(t_dongle));
	if (!p->dongle_left)
		return (1);
	p->dongle_left->state = D_FREE;
	p->dongle_left->id = p->id;
	if (p->id > 1)
		p->dongle_right = p[-1].dongle_left;
	gettimeofday(&p->dongle_left->time_released, NULL);
	p->dongle_left->time_released.tv_sec -= 1;
	p->debug = 1e+3 * data->time_db;
	p->compile = 1e+3 * data->time_cp;
	p->refactor = 1e+3 * data->time_rf;
	p->death = 1e+3 * data->time_bo;
	p->dead = 0;
	p->loops = data->nb_req_cp;
	if (i == (int)(data->n_of_p - 1))
		data->coders[0].dongle_right = p->dongle_left;
	p->n_of_p = data->n_of_p;
	gettimeofday(&p->ts_last_cp, NULL);
	p->shared = &data->shared;
	p->lefty = &data->coders[(i + 1) % data->n_of_p];
	p->righty = &data->coders[(i + data->n_of_p - 1) % data->n_of_p];
	p->state = CODER_INIT;
	return (0);
}

int	parse_to_data(char *argv[], t_data *data, int argc)
{
	if (check_args(argv, argc))
	{
		fprintf(stderr, "Error: one of the numbers has bad format");
		return (1);
	}
	data->n_of_p = atoi(argv[1]);
	data->time_bo = atoi(argv[2]);
	data->time_cp = atoi(argv[3]);
	data->time_db = atoi(argv[4]);
	data->time_rf = atoi(argv[5]);
	data->nb_req_cp = atoi(argv[6]);
	data->dongle_cd = atoi(argv[7]);
	if (!strcmp(argv[8], "fifo"))
		data->shared.dongle_center.scheduler = FIFO;
	else if (!strcmp(argv[8], "edf"))
		data->shared.dongle_center.scheduler = EDF;
	else
	{
		fprintf(stderr,
			"Error: scheduler has bad format, must be 'edf' or 'fifo'");
		return (1);
	}
	return (0);
}

int	init_shared(t_data *data)
{
	pthread_mutex_init(&(data->shared.dead_mutex), NULL);
	pthread_mutex_init(&(data->shared.print_mutex), NULL);
	data->shared.dongle_center.cooldown = data->dongle_cd;
	pthread_cond_init(&data->shared.dongle_center.changed_cond, NULL);
	data->shared.dongle_center.count = data->n_of_p;
	data->shared.dongle_center.ticket = 0;
	data->shared.dongle_center.stopping = 0;
	pthread_mutex_init(&(data->shared.dongle_center.mutex), NULL);
	gettimeofday(&data->shared.start_time, NULL);
	data->shared.coders_down = 0;
	data->shared.coder_down = 0;
	return (0);
}

int	init_data(char *argv[], t_data *data, int argc)
{
	int	i;

	if (argc != 9)
		return (print_instructions());
	i = 0;
	if (parse_to_data(argv, data, argc))
		return (1);
	if (init_shared(data))
		return (1);
	data->end_of_exe = 0;
	data->monitor = (pthread_t){0};
	data->coders = ft_calloc((data->n_of_p + 1), sizeof(t_coder));
	if (!data->coders)
		return ((destroy_all_pthread(data) + 1));
	i = -1;
	while (++i < (int)data->n_of_p)
		if (init_coder(&data->coders[i], i, data))
			return ((cleanup_below(data, i) + 1));
	return (0);
}
