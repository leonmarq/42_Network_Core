#include "push_swap.h"

static
char	*strat_toString(int strat)
{
	if (strat == SIMPLE)
		return ("Simple / O(n²)");
	else if (strat == MEDIUM)
		return ("Medium / O(n√n)");
	else if (strat == COMPLEX)
		return ("Complex / O(n log n)");
	else if (strat == ADAPTIVE)
		return ("Adaptive / O(n log n)");
	else
		return ("Adaptive / O(n log n)");
}

int bench_conditional_increment(t_bench *x, int op)
{
	if (x)
	{
		x->total++;
		x->op[op]++;
	}
	return (0);
}

double	compute_disorder(x_list *a)
{
	double	mistakes;
	double	total_pairs;
	x_list	*i;
	x_list	*j;

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

void	bench_print_report(t_bench *b, int strat, double disorder_percent)
{
	char	*pref;
	char	*strategy;
	int		disorder_frac;
	int		disorder_whole;

	pref = "[bench]";
	disorder_whole = (int)disorder_percent;
	disorder_frac = (int)((disorder_percent - (double)disorder_whole) * 100.0 + 0.5);
	ft_dprintf("%s disorder: %20d.%-02d%%\n", pref, disorder_whole, disorder_frac);
	strategy = strat_toString(strat);
	ft_dprintf("%s strategy: %24s\n", pref, strategy);
	ft_dprintf("%s total ops: %23u\n", pref, b->total);
	ft_dprintf("%s sa: %5u sb: %5u ss: %5u pa: %5u pb: %5u \n", pref, b->op[OP_SA], b->op[OP_SB], b->op[OP_SS], b->op[OP_PA], b->op[OP_PB]);
	ft_dprintf("%s ra: %5u rb: %5u rr: %5u rra: %4u rrb: %4u rrr: %4u\n", pref, b->op[OP_RA], b->op[OP_RB], b->op[OP_RR], b->op[OP_RRA], b->op[OP_RRB], b->op[OP_RRR]);
}
