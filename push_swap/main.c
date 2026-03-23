/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:33:41 by leon              #+#    #+#             */
/*   Updated: 2026/03/23 09:41:14 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/push_swap.h"

static
int	set_strat(char *s, int *strat)
{
	if (ft_strncmp("--simple", s, 15) == 0)
		*strat = (SIMPLE);
	else if (ft_strncmp("--medium", s, 15) == 0)
		*strat = (MEDIUM);
	else if (ft_strncmp("--complex", s, 15) == 0)
		*strat = (COMPLEX);
	else if (ft_strncmp("--adaptive", s, 15) == 0)
		*strat = (ADAPTIVE);
	else
		return (0);
	return (1);
}

static
int	parse_opts(int argc, char **argv, t_opts *o)
{
	int	i;

	o->strat = DEFAULT;
	o->bench = 0;
	i = 1;
	while (i < argc && ft_strncmp("--", argv[2], 2) == 0)
	{
		if (ft_strncmp("--bench", argv[i], 15) == 0)
			o->bench = 1;
		else if (!set_strat(argv[i], &o->strat))
			return (1);
		i++;
	}
	o->first_value = i;
	if (o->first_value >= argc)
		return (1);
	return (0);
}

int	fill_list(x_list *a, int argc, char **argv, t_opts *opts)
{
	int		i;

	if (parse_opts(argc, argv, opts))
		return (1);
	i = opts->first_value;
	while (i < (argc - 1))
	{
		a->next = NULL;
		if (!a || ft_atoicheck(argv[i + 1]) == (long)2147483648)
			return (1);
		a->x = (int)ft_atoicheck(argv[i + 1]);
		a->p = 0;
		if (!(++i < (argc - 1)))
			break ;
		a->next = ft_calloc(1, sizeof(x_list));
		a->opts = opts;
		a = a->next;
	}
	a->next = NULL;
	return (0);
}

int	check_list(x_list *a)
{
	x_list	*t1;
	x_list	*t2;
	int		i1;
	int		i2;

	t1 = a;
	if (a->next == NULL)
		return (0);
	i1 = 0;
	while (t1)
	{
		i2 = 0;
		t2 = a;
		while (t2)
		{
			if (t1->x == t2->x && i1 != i2)
				return (1);
			t2 = t2->next;
			i2++;
		}
		t1 = t1->next;
		i1++;
	}
	return (0);
}

int	free_list(x_list *a)
{
	x_list	*temp;

	while (a)
	{
		temp = a;
		a = a->next;
		free(temp);
	}
	return (0);
}

double compute_disorder(x_list *a)
{
	double	mistakes;
	double	total_pairs;
	int i;
	int j;

	mistakes = 0.0;
	total_pairs = 0.0;
	i = 0;
	while (i < get_size(a) - 1)
	{
		j = i + 1;
		while (j < get_size(a) - 1)
		{
			total_pairs += 1;
			if (get_index(a, i) < get_index(a, j))
				mistakes += 1;
			j++;
		}
		i++;
	}
	return ((mistakes * 100.0) / total_pairs);
}

int	main(int argc, char **argv)
{
	x_list		*a;
	x_list		*b;
	t_opts		o;
	double		disorder;

	if (argc < 2)
		return (0);
	a = malloc(sizeof(x_list));
	b = NULL;
	if (fill_list(a, argc, argv, &o) != 0)
	{
		err();
		free_list(a);
		return (1);
	}
	if (check_list(a) != 0)
	{
		err();
		free_list(a);
		return (1);
	}
	disorder = compute_disorder(a);
	bench_reset();
	bench_enable(o.bench);
	push_swap(&a, &b);
	bench_print_report(o.strat, disorder);
	free_list(a);
	return (1);
}
