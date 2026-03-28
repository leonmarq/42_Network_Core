/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 18:26:12 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/27 19:07:47 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	str_count_numbers(char *s)
{
	char	**split;
	int		total;

	split = ft_split(s, ' ');
	if (!split)
		return (-1);
	if (!split[0])
	{
		free_arr(split);
		return (0);
	}
	total = arr_size(split);
	free_arr(split);
	return (total);
}

static int	count_total_tokens(char **argv, int argc, int start)
{
	int		total;
	int		k;

	total = 0;
	k = start;
	while (k < argc)
	{
		if (argv[k] == NULL || argv[k][0] == '\0')
			return (0);
		if (ft_strchr(argv[k], ' '))
			total += str_count_numbers(argv[k]);
		else
			total++;
		k++;
	}
	return (total);
}

char	**arr_cat(char **dst, char **src, int *dst_i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dst[*dst_i] = ft_strdup(src[j]);
		if (!dst[*dst_i])
		{
			free_arr(src);
			return (free_arr(dst));
		}
		(*dst_i)++;
		(j)++;
	}
	return (dst);
}

char	**parse_string(char *str, char **input, int *dst_i)
{
	char	**split;

	split = ft_split(str, ' ');
	if (!split)
		return (free_arr(input));
	if (!split[0])
	{
		free_arr(split);
		err();
		return (free_arr(input));
	}
	input = arr_cat(input, split, dst_i);
	free_arr(split);
	return (input);
}

char	**allocate_input(char **argv, int argc, int k)
{
	char	**input;
	int		dst_i;
	int		total;

	total = count_total_tokens(argv, argc, k);
	if (total <= 0)
		return (NULL);
	input = ft_calloc(total + 1, sizeof(char *));
	if (!input)
		return (NULL);
	dst_i = 0;
	if (argv[k] == NULL || argv[k][0] == '\0')
		return (free_arr(input));
	while (k < argc)
	{
		if (ft_strchr(argv[k], ' '))
			input = parse_string(argv[k], input, &dst_i);
		else
			input[dst_i++] = ft_strdup(argv[k]);
		if (!input || !input[dst_i - 1])
			return (free_arr(input));
		k++;
	}
	return (input);
}
