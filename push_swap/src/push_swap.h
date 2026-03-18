/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:37:07 by leon              #+#    #+#             */
/*   Updated: 2022/04/08 16:03:55 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include "../libft/libft.h"

typedef struct s_list
{
	int				x;
	int				p;	
	struct s_list	*next;
}	t_list;
int		printlists(t_list *a, t_list *b);
int		push_swap(t_list **a, t_list **b);
long	ft_atoicheck(char *nptr);
int		err(void);

int		sa(t_list *a);
int		sb(t_list *b);
int		ss(t_list *a, t_list *b);
int		pa(t_list **a, t_list **b);
int		pb(t_list **a, t_list **b);
int		ra(t_list **a);
int		rb(t_list **b);
int		rr(t_list **a, t_list **b);
int		rra(t_list **a);
int		rrb(t_list **b);
int		sort(t_list **a, t_list **b);

int		b_to_a(t_list **a, t_list **b);
int		b_to_a_rev(t_list **a, t_list **b);
int		a_to_b(t_list **a, t_list **b);
int		a_to_b_rev(t_list **a, t_list **b);
int		sort3(t_list **a, t_list **b, int k);
int		sort3_b_pa(t_list **a, t_list **b, int k);
int		find_median(t_list *a);
int		find_median_end(t_list *a);
int		get_size(t_list *x);
int		get_size_end(t_list *x);
int		p_to_null(t_list *a);
int		sorted(t_list *a);
int		get_last(t_list *x);
int		get_last_p(t_list *x);
int		get_biggest(t_list *x);
#endif
