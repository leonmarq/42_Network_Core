/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:30:35 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:30:35 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		arr[500];
	size_t	i;

	i = 0;
	while (i < n)
	{
		arr[i] = *((char *)src + i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		*((char *)dest + i) = arr[i];
		i++;
	}
	return (dest);
}
