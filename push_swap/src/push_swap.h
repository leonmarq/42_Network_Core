/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:07 by leon              #+#    #+#             */
/*   Updated: 2026/03/25 13:26:28 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include "../ft_dprintf/ft_dprintf.h"

# define DEFAULT 0
# define SIMPLE 1
# define MEDIUM 2
# define COMPLEX 3
# define ADAPTIVE 4

typedef enum e_op_type
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_op_type;

typedef struct s_bench
{
	unsigned long	total;
	unsigned long	op[OP_COUNT];
}	t_bench;

typedef struct s_opts
{
	int		strat;
	int		debug;
	double	disorder;
	t_bench	*bench;
	int		first_value;
}	t_opts;

typedef struct p_list
{
	int				x;
	int				p;
	struct s_opts	*opts;
	struct p_list	*next;
}	t_slist;

double	compute_disorder(t_slist *a);
int		bench_conditional_increment(t_bench *x, int op);
void	bench_print_report(t_bench *b, int strat, double disorder_percent);
int		printlists(t_slist *a, t_slist *b);
int		push_swap(t_slist **a, t_slist **b);
long	ft_atoicheck(char *nptr);
int		err(void);
int		ps_free_list(t_slist *a);
int		sa(t_slist *a);
int		sb(t_slist *b);
int		ss(t_slist *a, t_slist *b);
int		pa(t_slist **a, t_slist **b);
int		pb(t_slist **a, t_slist **b);
int		ra(t_slist **a);
int		rb(t_slist **b);
int		rr(t_slist **a, t_slist **b);
int		rra(t_slist **a);
int		rrb(t_slist **b);
int		rrr(t_slist **a, t_slist **b);
int		algorithm_complex(t_slist **a, t_slist **b);
int		algorithm_medium(t_slist **a, t_slist **b);
int		algorithm_simple(t_slist **a, t_slist **b);
int		b_to_a(t_slist **a, t_slist **b);
int		b_to_a_rev(t_slist **a, t_slist **b);
int		a_to_b(t_slist **a, t_slist **b);
int		a_to_b_rev(t_slist **a, t_slist **b);
int		sort3_a(t_slist **a, t_slist **b, int k);
int		sort3_b_pa(t_slist **a, t_slist **b, int k);
int		sort3_b_pa_rev(t_slist **a, t_slist **b);
int		find_median(t_slist *a);
int		find_median_end(t_slist *a);
int		get_size_p(t_slist *x);
int		get_size(t_slist *x);
int		get_size_end_p(t_slist *x);
int		p_to_null(t_slist *a);
int		check_sorted(t_slist *a);
int		get_last(t_slist *x);
int		get_last_p(t_slist *x);
int		get_biggest(t_slist *x);
int		get_biggest_p(t_slist *x);
void	free_pslist(t_slist *x);
int		min(int a, int b);
t_slist	*get_index(t_slist *x, int p);

#endif
