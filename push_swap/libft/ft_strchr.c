/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:30:34 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:30:34 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = c % 256;
	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (!s[i] && c)
		return (NULL);
	else
		return ((char *)&s[i]);
}
