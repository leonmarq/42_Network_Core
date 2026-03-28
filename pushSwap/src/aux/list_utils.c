/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:49:31 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/27 17:45:37 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_slist	*arr_to_list(char **arr, t_slist *a)
{
	int		i;
	t_opts	*opts;
	t_slist	*a_t;

	i = 0;
	opts = a->opts;
	a_t = a;
	while (arr[i])
	{
		if (ft_atoicheck(arr[i]) == (long)2147483648)
			return (NULL);
		a_t->x = (int)ft_atoicheck(arr[i]);
		a_t->p = 0;
		a_t->next = NULL;
		a_t->opts = opts;
		i++;
		if (!arr[i])
			break ;
		a_t->next = ft_calloc(1, sizeof(t_slist));
		if (!a_t->next)
			return (NULL);
		a_t = a_t->next;
	}
	a_t->next = NULL;
	return (a);
}

int	fill_list(t_slist *a, int argc, char **argv, t_opts *opts)
{
	int		i;
	char	**input;
	t_slist	*a_t;

	if (parse_opts(argc, argv, opts))
		return (1);
	i = opts->first_value;
	input = allocate_input(argv, argc, i);
	if (!input)
		return (1);
	a->opts = opts;
	a_t = a;
	a_t = arr_to_list(input, a);
	free_arr(input);
	if (!a_t)
		return (1);
	return (0);
}
