/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:30:29 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/19 11:48:15 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*trim(char const *s, char i)
{
	int		j;
	char	*ret;

	ret = ft_calloc(i + 1, 1);
	if (ret)
	{
		j = 0;
		while (j < i && s[j])
		{
			ret[j] = s[j];
			j++;
		}
	}
	return (ret);
}

int	count_substr(char const *s, char c)
{
	int	i;
	int	r;

	r = 0;
	while (*s)
	{
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i)
			r++;
		while (s[i] && s[i] == c)
			i++;
		s = s + i;
	}
	return (r);
}

void	**dp_free(void **a)
{
	void **t;

	t = a;
	while (*t)
	{
		t++;
		free(t - 1);
	}
	free(a);
	return (a);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	**t;
	int		i;

	if (!s)
		return (NULL);
	i = count_substr(s, c);
	res = ft_calloc(i + 1, sizeof(char *));
	if (!res)
		return (NULL);
	t = res;
	while (*s)
	{
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i)
		{
			*(t++) = trim(s, i);
			if (!(*(t - 1)))
				return ((char **)dp_free((void **)res));
		}
		while (s[i] && s[i] == c)
			i++;
		s = s + i;
	}
	return (res);
}
