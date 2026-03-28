/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:26:51 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/26 16:31:09 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	fsqurt(float num)
{
	int		i;
	float	f;

	i = *(int *)&num;
	i = (i >> 1) + 0x1fbb67ae;
	f = *(float *)&i;
	f = 0.5F * (f + num / f);
	return (f);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
