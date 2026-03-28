/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:49:31 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 11:22:26 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	arr_to_list(char **arr, t_slist **a)
{
	int		i;
	t_opts	*opts;
	t_slist	*a_t;

	i = 0;
	opts = (*a)->opts;
	a_t = *a;
	while (arr[i])
	{
		if (ft_atoicheck(arr[i]) == (long)2147483648)
			return (1);
		a_t->x = (int)ft_atoicheck(arr[i]);
		a_t->p = 0;
		a_t->next = NULL;
		a_t->opts = opts;
		i++;
		if (!arr[i])
			break ;
		a_t->next = ft_calloc(1, sizeof(t_slist));
		if (!a_t->next)
			return (1);
		a_t = a_t->next;
	}
	a_t->next = NULL;
	return (0);
}

int	fill_list(t_slist **a, int argc, char **argv, t_opts *opts)
{
	int		i;
	char	**input;

	if (parse_opts(argc, argv, opts))
		return (1);
	i = opts->first_value;
	input = allocate_input(argv, argc, i);
	if (!input)
		return (1);
	(*a)->opts = opts;
	if (arr_to_list(input, a))
		i = 1;
	else
		i = 0;
	free_arr(input);
	return (i);
}
