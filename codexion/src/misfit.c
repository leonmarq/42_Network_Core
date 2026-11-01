/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misfit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:20:43 by leon              #+#    #+#             */
/*   Updated: 2026/07/01 08:44:09 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	all_coders_down(t_data *data)
{
	int			f;
	long long	i;

	i = 0;
	f = 1;
	while (i < data->n_of_p)
	{
		if (!(data->coders[i].dead || data->coders[i].done))
			f = 0;
		i++;
	}
	if (f)
		data->shared.coders_down = 1;
	return (f);
}

int	p_set_dead(t_coder *p)
{
	pthread_mutex_lock(&p->shared->dead_mutex);
	p->dead = 1;
	p->shared->coder_down = 1;
	pthread_mutex_unlock(&p->shared->dead_mutex);
	return (0);
}

int	check_if_dead(t_coder *p)
{
	int	ret;

	pthread_mutex_lock(&p->shared->dead_mutex);
	ret = p->shared->coder_down;
	pthread_mutex_unlock(&p->shared->dead_mutex);
	return (ret);
}

int	m_printf_func(t_coder *p, t_action i)
{
	pthread_mutex_lock(&p->shared->print_mutex);
	if (i == CODER_TAKES)
		printf("%10lld %d has taken a dongle\n", time_ms(p->shared->start_time),
			p->id);
	else if (i == CODER_COMPILE)
		printf("%10lld %d is compiling\n", time_ms(p->shared->start_time),
			p->id);
	else if (i == CODER_DEBUG)
		printf("%10lld %d is debugging\n", time_ms(p->shared->start_time),
			p->id);
	else if (i == CODER_REFACTOR)
		printf("%10lld %d is refactoring\n", time_ms(p->shared->start_time),
			p->id);
	else if (i == CODER_BURNOUT)
		printf("%10lld %d burned out\n", time_ms(p->shared->start_time), p->id);
	else if (i == CODER_COMPLETED)
		printf("%10lld %d completed required compiles\n",
			time_ms(p->shared->start_time), p->id);
	pthread_mutex_unlock(&p->shared->print_mutex);
	return (0);
}

int	print_instructions(void)
{
	fprintf(stderr, "Error: too few arguments");
	return (1);
}
