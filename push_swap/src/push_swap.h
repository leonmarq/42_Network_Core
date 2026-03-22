/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:07 by leon              #+#    #+#             */
/*   Updated: 2026/03/22 10:14:07 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include "../libft/libft.h"

# define DEFAULT 0
# define SIMPLE 1
# define MEDIUM 2
# define COMPLEX 3
# define ADAPTIVE 4

typedef struct p_list
{
	int				x;
	int				p;
	struct p_list	*next;
}	x_list;

typedef struct s_opts
{
	int	strat;
	int	bench;
	int	first_value;
}	t_opts;

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
	int				enabled;
	unsigned long	total;
	unsigned long	op[OP_COUNT];
}	t_bench;

void	bench_reset(void);
void	bench_enable(int enabled);
void	bench_count(t_op_type op);
void	bench_print_report(int strat, double disorder_percent);

int		printlists(x_list *a, x_list *b);

int		push_swap(x_list **a, x_list **b, int strat, t_bench *bench);
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
int		sort3(x_list **a, x_list **b, int k);
int		sort3_b_pa(x_list **a, x_list **b, int k);
int		find_median(x_list *a);
int		find_median_end(x_list *a);
int		get_size(x_list *x);
int		get_size_end(x_list *x);
int		p_to_null(x_list *a);
int		sorted(x_list *a);
int		get_last(x_list *x);
int		get_last_p(x_list *x);
int		get_biggest(x_list *x);
int 	min(int a, int b);
x_list	*get_index(x_list *x, int p);

#endif
