/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:28:01 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:28:01 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	i;
	size_t	sn;

	sn = 9223372036854775807ULL;
	if (nmemb <= 0 || size <= 0)
		return (malloc(0));
	if (nmemb > sn || size > sn)
		return (0);
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
