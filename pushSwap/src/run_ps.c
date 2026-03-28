/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:13:24 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 11:08:18 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_list(t_slist *a)
{
	t_slist	*t1;
	t_slist	*t2;
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

int	based_on_disorder(double disorder)
{
	if (disorder < 0.2)
		return (COMPLEX);
	else if (disorder < 0.5)
		return (MEDIUM);
	else
		return (COMPLEX);
}

static
char	*strat_to_string(int strat, double disorder)
{
	if (strat == SIMPLE)
		return ("Simple / O(n²)");
	else if (strat == MEDIUM)
		return ("Medium / O(n√n)");
	else if (strat == COMPLEX)
		return ("Complex / O(n log n)");
	else if (strat == ADAPTIVE && disorder < 20.0)
		return ("Adaptive / O(n)");
	else if (strat == ADAPTIVE && disorder < 50.0)
		return ("Adaptive / O(n√n)");
	else
		return ("Adaptive / O(n log n)");
}

int	run_ps(int argc, char **argv)
{
	t_slist	*a;
	t_slist	*b;
	t_opts	o;

	if (argc < 2)
		return (0);
	a = ft_calloc(1, sizeof(t_slist));
	b = NULL;
	if (fill_list(&a, argc, argv, &o) != 0 || check_list(a) != 0)
	{
		err();
		ps_free_list(a);
		return (1);
	}
	o.disorder = compute_disorder(a);
	o.strat_name = strat_to_string(o.strat, o.disorder);
	if (o.strat == ADAPTIVE)
		o.strat = based_on_disorder(o.disorder);
	push_swap(&a, &b);
	if (o.bench)
		bench_print_report(o);
	ps_free_list(a);
	return (1);
}
