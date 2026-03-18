/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:30:14 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:30:14 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*res;

	res = NULL;
	i = 0;
	while (i < n && ((char *)src)[i])
	{
		if (*((char *)(src + i)) == c)
		{
			*((char *)(dest + i)) = *((char *)(src + i));
			res = &*((char *)(dest + i + 1));
			break ;
		}
		*((char *)(dest + i)) = *((char *)(src + i));
		i++;
	}
	if (i == n)
		return (NULL);
	return (res);
}
