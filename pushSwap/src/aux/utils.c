/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:45:32 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 12:27:17 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	**arr_cpy(char **arr, int size)
{
	char	**cpy;
	int		i;

	cpy = ft_calloc((size) + 2, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (arr[i] && i < size)
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	return (cpy);
}

void	*free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	parse_opts(int argc, char **argv, t_opts *o)
{
	int	i;

	o->strat = ADAPTIVE;
	o->debug = 0;
	o->bench = NULL;
	o->disorder = 0.0;
	o->first_value = 0;
	i = 1;
	while (i < argc && ft_strncmp("--", argv[i], 2) == 0)
	{
		if (ft_strncmp("--bench", argv[i], 15) == 0 && !o->bench)
			o->bench = ft_calloc(1, sizeof(t_bench));
		else if (ft_strncmp("--debug", argv[i], 15) == 0)
			o->debug = 1;
		else if (!set_strat(argv[i], &o->strat))
			return (1);
		i++;
	}
	o->first_value = i;
	if (o->first_value >= argc)
		return (1);
	return (0);
}

int	err(void)
{
	char	*s;
	int		i;

	s = "Error\n";
	i = 0;
	while (s[i])
	{
		write(2, &(s[i]), 1);
		i++;
	}
	return (-1);
}
