/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarquar <lmarquar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:31:15 by lmarquar          #+#    #+#             */
/*   Updated: 2021/06/04 13:31:15 by lmarquar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	res = ft_calloc(i + 1, 1);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}
