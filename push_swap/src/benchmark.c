/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:12:19 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/27 15:13:01 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	bench_conditional_increment(t_bench *x, int op)
{
	if (x)
	{
		x->total++;
		x->op[op]++;
	}
	return (0);
}

double	compute_disorder(t_slist *a)
{
	double	mistakes;
	double	total_pairs;
	t_slist	*i;
	t_slist	*j;

	mistakes = 0.0;
	total_pairs = 0.0;
	i = 0;
	i = a;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			total_pairs += 1.0;
			if (i->x > j->x)
				mistakes += 1.0;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0.0)
		return (0.0);
	return ((mistakes * 100.0) / total_pairs);
}

void	bench_print_report(t_opts o)
{
	char	*pref;
	int		dis_frac;
	int		dis_whole;
	t_bench	*b;

	b = o.bench;
	pref = "[bench]";
	dis_whole = (int)o.disorder;
	dis_frac = (int)((o.disorder - (double)dis_whole) * 100.0 + 0.5);
	ft_dprintf(2, "%s disorder: %20d.%-02d%%\n",
		pref, dis_whole, dis_frac);
	ft_dprintf(2, "%s strategy: %24s\n", pref, o.strat_name);
	ft_dprintf(2, "%s total ops: %23u\n", pref, b->total);
	ft_dprintf(2, "%s sa: %5u ", pref, b->op[OP_SA]);
	ft_dprintf(2, "sb: %5u ss: %5u ", b->op[OP_SB], b->op[OP_SS]);
	ft_dprintf(2, "pa: %5u pb: %5u\n", b->op[OP_PA], b->op[OP_PB]);
	ft_dprintf(2, "%s ra: %5u rb: ", pref, b->op[OP_RA]);
	ft_dprintf(2, "%5u rr: %5u ", b->op[OP_RB], b->op[OP_RR]);
	ft_dprintf(2, "rra: %4u rrb: %4u ", b->op[OP_RRA], b->op[OP_RRB]);
	ft_dprintf(2, "rrr: %4u\n", b->op[OP_RRR]);
}
