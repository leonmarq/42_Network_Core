/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:31:54 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:31:54 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	i2;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		i2 = 0;
		while (big[i + i2] == little[i2] && (i + i2) < len && big[i + i2])
		{
			i2++;
			if (!little[i2])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
