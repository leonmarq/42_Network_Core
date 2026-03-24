/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:33:41 by leon              #+#    #+#             */
/*   Updated: 2026/03/24 20:15:53 by leonmarq         ###   ########.fr       */
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

int	fill_list(x_list *a, int argc, char **argv, t_opts *opts)
{
	int		i;

	if (parse_opts(argc, argv, opts))
		return (1);
	i = opts->first_value;
	while (i < argc)
	{
		if (!a)
			return (1);
		if (ft_atoicheck(argv[i]) == (long)2147483648)
			return (1);
		a->x = (int)ft_atoicheck(argv[i]);
		a->p = 0;
		a->next = NULL;
		a->opts = opts;
		i++;
		if (i >= argc)
			break ;
		a->next = ft_calloc(1, sizeof(x_list));
		if (!a->next)
			return (1);
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

int	main(int argc, char **argv)
{
	x_list	*a;
	x_list	*b;
	t_opts	o;

	if (argc < 2)
		return (0);
	a = malloc(sizeof(x_list));
	b = NULL;
	if (fill_list(a, argc, argv, &o) != 0 || check_list(a) != 0)
	{
		err();
		ps_free_list(a);
		return (1);
	}
	o.disorder = compute_disorder(a);
	push_swap(&a, &b);
	if (o.bench)
		bench_print_report(o.bench, o.strat, o.disorder);
	ps_free_list(a);
	return (1);
}
