/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:16:57 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 13:42:40 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	execute_command(char *command, t_slist **a, t_slist **b)
{
	if (ft_strncmp(command, "rra", 3) == 0)
		rra_ckr(a);
	else if (ft_strncmp(command, "rrb", 3) == 0)
		rrb_ckr(b);
	else if (ft_strncmp(command, "rrr", 3) == 0)
		rrr_ckr(a, b);
	else if (ft_strncmp(command, "sa", 2) == 0)
		sa_ckr(*a);
	else if (ft_strncmp(command, "sb", 2) == 0)
		sb_ckr(*b);
	else if (ft_strncmp(command, "ss", 2) == 0)
		ss_ckr(*a, *b);
	else if (ft_strncmp(command, "pa", 2) == 0)
		pa_ckr(a, b);
	else if (ft_strncmp(command, "pb", 2) == 0)
		pb_ckr(a, b);
	else if (ft_strncmp(command, "ra", 2) == 0)
		ra_ckr(a);
	else if (ft_strncmp(command, "rb", 2) == 0)
		rb_ckr(b);
	else if (ft_strncmp(command, "rr", 2) == 0)
		rr_ckr(a, b);
	else
		return (1);
	return (0);
}

t_slist	*start_new_slist(void)
{
	t_bench	*bench;
	t_opts	*opts;
	t_slist	*head;

	bench = ft_calloc(1, sizeof(t_bench));
	opts = ft_calloc(1, sizeof(t_opts));
	opts->bench = bench;
	head = ft_calloc(1, sizeof(t_slist));
	head->opts = opts;
	return (head);
}

int	ckr_free_list(t_slist *x)
{
	t_slist	*temp;

	if (!x)
		return (0);
	while (x)
	{
		temp = x;
		x = x->next;
		free(temp);
	}
	return (0);
}

int	free_opts(t_opts *opts)
{
	free(opts->bench);
	free(opts);
	return (0);
}
