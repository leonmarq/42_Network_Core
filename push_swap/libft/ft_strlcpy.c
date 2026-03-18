/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:31:34 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:31:34 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while ((i + 1) < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i || !(*src))
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
