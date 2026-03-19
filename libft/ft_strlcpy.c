/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:30:59 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:30:59 by leonmarq         ###   ########.fr       */
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
	if (i || !(*src) || size == 1)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
