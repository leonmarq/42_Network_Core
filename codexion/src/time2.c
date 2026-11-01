/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:11:06 by leonmarq          #+#    #+#             */
/*   Updated: 2026/06/25 16:11:07 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

struct timeval	time_in(int ms)
{
	struct timeval	ts;

	gettimeofday(&ts, NULL);
	return (add_time(ts, ms));
}
