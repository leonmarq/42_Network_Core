/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:31:29 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:31:29 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	i2;

	i = 0;
	while (dst[i] && i < size)
		i++;
	i2 = 0;
	while (src[i2] && (i + i2 + 1) < size)
	{
		dst[i + i2] = src[i2];
		i2++;
	}
	if (i2 > 0)
		dst[i + i2] = '\0';
	while (src[i2])
		i2++;
	return (i2 + i);
}
