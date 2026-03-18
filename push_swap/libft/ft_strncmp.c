/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:31:49 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:31:49 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (s1[i] == s2[i] && i < (n - 1) && s1[i] && s2[i])
		i++;
	if (n > 0)
		res = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
	return (res);
}
