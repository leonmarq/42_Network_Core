/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:31:47 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:31:47 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			i;
	size_t			slen;

	if (ft_strlen(s) < start)
		return (ft_calloc(1, sizeof(char)));
	slen = ft_strlen(&(s[start]));
	if (slen < len)
		len = slen;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len && s[start])
	{
		res[i] = s[start];
		i++;
		start++;
	}
	return (res);
}
