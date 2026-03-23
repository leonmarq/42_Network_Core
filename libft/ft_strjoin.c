/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:30:50 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:30:50 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	char	*res;

	i = 0;
	i2 = 0;
	while (s1[i])
		i++;
	while (s2[i2])
		i2++;
	res = malloc(i + i2 + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i2 = 0;
	while (s2[i2])
	{
		res[i + i2] = s2[i2];
		i2++;
	}
	res[i + i2] = '\0';
	return (res);
}
