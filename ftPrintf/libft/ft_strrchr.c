/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:31:33 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:31:33 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	c = c % 256;
	i = 0;
	while (s[i])
		i++;
	while (i > 0 && s[i] != c)
		i--;
	if (s[i] != c)
		return (NULL);
	else
		return ((char *)&s[i]);
}
