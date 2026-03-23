/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:07 by leon              #+#    #+#             */
/*   Updated: 2026/03/23 18:18:12 by leonmarq         ###   ########.fr       */
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
}	x_list;

int		bench_conditional_increment(t_bench *x, int op);
void 	bench_print_report(t_bench *b, int strat, double disorder_percent);

int		printlists(x_list *a, x_list *b);

int		push_swap(x_list **a, x_list **b);
long	ft_atoicheck(char *nptr);
int		err(void);

int		sa(x_list *a);
int		sb(x_list *b);
int		ss(x_list *a, x_list *b);
int		pa(x_list **a, x_list **b);
int		pb(x_list **a, x_list **b);
int		ra(x_list **a);
int		rb(x_list **b);
int		rr(x_list **a, x_list **b);
int		rra(x_list **a);
int		rrb(x_list **b);
int		rrr(x_list **a, x_list **b);
int		algorithm_complex(x_list **a, x_list **b);
int		algorithm_medium(x_list **a, x_list **b);
int		algorithm_simple(x_list **a, x_list **b);

int		b_to_a(x_list **a, x_list **b);
int		b_to_a_rev(x_list **a, x_list **b);
int		a_to_b(x_list **a, x_list **b);
int		a_to_b_rev(x_list **a, x_list **b);
int 	sort3_a(x_list **a, x_list **b, int k);
int		sort3_b_pa(x_list **a, x_list **b, int k);
int		find_median(x_list *a);
int		find_median_end(x_list *a);
int		get_size_p(x_list *x);
int 	get_size(x_list *x);
int		get_size_end_p(x_list *x);
int		p_to_null(x_list *a);
int		sorted(x_list *a);
int		get_last(x_list *x);
int		get_last_p(x_list *x);
int		get_biggest(x_list *x);
int 	min(int a, int b);
x_list	*get_index(x_list *x, int p);

#endif
