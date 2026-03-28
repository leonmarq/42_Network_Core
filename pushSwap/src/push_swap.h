/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:07 by leon              #+#    #+#             */
/*   Updated: 2026/03/28 11:20:20 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include "../ft_dprintf/ft_dprintf.h"
# include "../get_next_line/get_next_line.h"

# define DEFAULT 0
# define SIMPLE 1
# define MEDIUM 2
# define COMPLEX 3
# define ADAPTIVE 4

typedef struct s_chunk
{
	int		count;
	int		size;
}	t_chunk;

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
	char	*strat_name;
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
void	bench_print_report(t_opts o);
int		printlists(t_slist *a, t_slist *b);
int		printdparray(char **arr);
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
t_slist	*get_by_x(t_slist *stack, int x);
t_slist	*find_next_lowest(t_slist *stack, t_slist *current);
int		sort_by_chunk(t_slist **a, t_slist **b, t_chunk chunk);
int		top_value_closer(t_slist *b, int value);
int		top_chunk_closer(t_slist *a, int chunk);
int		assign_ranks_to_p(t_slist *stack);
t_chunk	gen_chunks(t_slist **a);
int		sort_loop(t_slist **a, t_slist **b);
int		get_size_p(t_slist *x);
int		get_size(t_slist *x);
int		get_size_end_p(t_slist *x);
int		p_to_null(t_slist *a);
int		check_sorted(t_slist *a);
int		get_last(t_slist *x);
char	**arr_cpy(char **arr, int size);
void	*free_arr(char **arr);
int		arr_size(char **arr);
int		get_last_p(t_slist *x);
int		get_biggest(t_slist *x);
int		p_to_x(t_slist **stack);
int		get_biggest_p(t_slist *x);
void	free_pslist(t_slist *x);
int		min(int a, int b);
float	fsqurt(float num);
t_slist	*get_index(t_slist *x, int p);
int		fill_list(t_slist **a, int argc, char **argv, t_opts *opts);
int		arr_to_list(char **arr, t_slist **a);
char	**allocate_input(char **argv, int argc, int k);
int		parse_opts(int argc, char **argv, t_opts *o);
int		set_strat(char *s, int *strat);
int		run_ps(int argc, char **argv);

#endif
