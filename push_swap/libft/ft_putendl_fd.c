/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:30:50 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:30:50 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	n;

	i = 0;
	n = '\n';
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, &n, 1);
}
