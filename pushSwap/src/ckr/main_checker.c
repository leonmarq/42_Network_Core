/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:26:59 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 11:30:29 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	valid_command(char *command)
{
	if (ft_strncmp(command, "sa\n", 4) == 0
		|| ft_strncmp(command, "sb\n", 4) == 0
		|| ft_strncmp(command, "ss\n", 4) == 0
		|| ft_strncmp(command, "pa\n", 4) == 0
		|| ft_strncmp(command, "pb\n", 4) == 0
		|| ft_strncmp(command, "ra\n", 4) == 0
		|| ft_strncmp(command, "rb\n", 4) == 0
		|| ft_strncmp(command, "rr\n", 4) == 0
		|| ft_strncmp(command, "rra\n", 4) == 0
		|| ft_strncmp(command, "rrb\n", 4) == 0
		|| ft_strncmp(command, "rrr\n", 4) == 0)
		return (1);
	else
		return (0);
}

int	loop_command_execution(t_slist **a, t_slist **b)
{
	char	*command;

	while (1)
	{
		command = get_next_line(0);
		if (!command)
			break ;
		if (valid_command(command))
			execute_command(command, a, b);
		else
		{
			free(command);
			write(1, "Error\n", 6);
			return (1);
		}
		free(command);
		if (check_sorted(*a) && !*b)
			break ;
	}
	return (0);
}

static
int	create_list(int argc, char **argv, t_slist **a)
{
	char	**input;

	input = allocate_input(argv, argc, 1);
	if (!input)
	{
		write(1, "Error\n", 6);
		free_opts((*a)->opts);
		ckr_free_list(*a);
		return (1);
	}
	argc = arr_size(input);
	if (arr_to_list(input, a))
	{
		write(1, "Error\n", 6);
		free_arr(input);
		free_opts((*a)->opts);
		ckr_free_list(*a);
		return (1);
	}
	free_arr(input);
	return (0);
}

int free_lists(t_slist *a, t_slist *b)
{
	if (a)
		free_opts(a->opts);
	else
		free_opts(b->opts);
	ckr_free_list(a);
	ckr_free_list(b);
	return (1);
}

int	main(int argc, char **argv)
{
	t_slist	*a;
	t_slist	*b;

	a = start_new_slist();
	b = NULL;
	if (argc < 2)
		return (0);
	if (create_list(argc, argv, &a))
		return (1);
	if (loop_command_execution(&a, &b))
		return (free_lists(a, b));
	if (check_sorted(a) && !b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_lists(a, b);
	return (0);
}
