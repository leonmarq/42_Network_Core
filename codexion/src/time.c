/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 15:51:47 by leonmarq          #+#    #+#             */
/*   Updated: 2026/06/27 08:28:02 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	time_diff(struct timeval start, struct timeval end)
{
	long	res;

	res = 1e+6 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	return (res);
}

long	time_until(struct timeval end)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (time_diff(cur, end));
}

long long	time_ms(struct timeval start)
{
	struct timeval	x;
	long long		res;

	gettimeofday(&(x), NULL);
	res = (x.tv_sec - start.tv_sec) * 1000;
	res += (x.tv_usec - start.tv_usec) / 1000;
	return (res);
}

struct timeval	add_time(struct timeval ts, int ms)
{
	struct timeval	res;

	res.tv_sec = ts.tv_sec + ms / 1000000;
	res.tv_usec = ts.tv_usec + ms % 1000000;
	if (res.tv_usec >= 1000000)
	{
		res.tv_sec = res.tv_sec + 1;
		res.tv_usec = res.tv_usec % 1000000;
	}
	return (res);
}

long	time_to_long(struct timeval ts)
{
	return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}
