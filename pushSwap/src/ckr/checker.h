/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:45:16 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 13:49:16 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../push_swap.h"

# define MAX_COMMANDS 1000000

char	*get_next_line(int fd);
int		check_args(char *commands, int argc, char **argv);
int		execute_command(char *command, t_slist **a, t_slist **b);
int		sa_ckr(t_slist *a);
int		sb_ckr(t_slist *b);
int		ss_ckr(t_slist *a, t_slist *b);
int		pa_ckr(t_slist **a, t_slist **b);
int		pb_ckr(t_slist **a, t_slist **b);
int		ra_ckr(t_slist **a);
int		rb_ckr(t_slist **b);
int		rr_ckr(t_slist **a, t_slist **b);
int		rra_ckr(t_slist **a);
int		rrb_ckr(t_slist **b);
int		rrr_ckr(t_slist **a, t_slist **b);
t_slist	*start_new_slist(void);
int		ckr_free_list(t_slist *a);
int		free_opts(t_opts *opts);
int		is_commandnonl(char *command);
int		is_commandwnl(char *command);

#endif
