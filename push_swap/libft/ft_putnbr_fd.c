/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:30:54 by lmarquar          #+#    #+#             */
/*   Updated: 2022/04/08 16:13:09 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nl;

	nl = n;
	if (n == 0)
		c = '0';
	else if (nl < -9 || nl > 9)
	{
		if (nl < -9)
			c = ((nl * -1) % 10) + '0';
		else
			c = (nl % 10) + '0';
		nl = nl / 10;
		ft_putnbr_fd(nl, fd);
	}
	else if (nl < 0)
	{
		c = (nl * -1) + '0';
		write(fd, "-", 1);
	}
	else
		c = nl + '0';
	write(1, &c, 1);
}
