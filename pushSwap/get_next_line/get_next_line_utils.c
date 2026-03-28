/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:53:51 by lmarquar          #+#    #+#             */
/*   Updated: 2026/03/21 13:41:51 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_n(char **p)
{
	free(*p);
	*p = NULL;
}

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
