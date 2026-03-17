/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <leon.marquardt@gmx.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:53:51 by lmarquar          #+#    #+#             */
/*   Updated: 2021/07/04 18:23:12 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	i;
	size_t	sn;

	sn = 9223372036854775807ULL;
	if (nmemb <= 0 || size <= 0 || nmemb > sn || size > sn)
		return (malloc(0));
	sn = nmemb * size;
	s = (void *)malloc(sn);
	if (!s)
		return (0);
	i = 0;
	while (i < sn)
	{
		*((unsigned char *)s + i) = '\0';
		i++;
	}
	return (s);
}
