/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:29:46 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:29:46 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				res;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (i < (n - 1) && *(us1 + i) == *(us2 + i))
		i++;
	if (*(us1 + i) != *(us2 + i))
		res = *(us1 + i) - *(us2 + i);
	else
		res = 0;
	return (res);
}
