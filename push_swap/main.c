/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:33:41 by leon              #+#    #+#             */
/*   Updated: 2026/03/19 19:06:40 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/push_swap.h"

int	printlists(x_list *a, x_list *b)
{
	write(1, "a:\n", 3);
	while (a)
	{
		ft_putnbr_fd(a->x, 1);
		a = a->next;
		write(1, "\n", 1);
	}
	write(1, "\nb:\n", 4);
	while (b)
	{
		ft_putnbr_fd(b->x, 1);
		b = b->next;
		write(1, "\n", 1);
	}
	return (1);
}

int	get_strat(char **argv)
{
	if (ft_strncmp("--simple", argv[1], 15) == 0)
		return (SIMPLE);
	else if (ft_strncmp("--medium", argv[1], 15) == 0)
		return (MEDIUM);
	else if (ft_strncmp("--complex", argv[1], 15) == 0)
		return (COMPLEX);
	else if (ft_strncmp("--adaptive", argv[1], 15) == 0)
		return (ADAPTIVE);
	else
		return (DEFAULT);
}

int	fill_list(x_list *a, int argc, char **argv, int *strat)
{
	int		i;

	i = 0;
	*strat = get_strat(argv);
	if (*strat != DEFAULT)
		i++;
	while (i < (argc - 1))
	{
		a->next = NULL;
		if (!a || ft_atoicheck(argv[i + 1]) == (long)2147483648)
			return (1);
		a->x = (int)ft_atoicheck(argv[i + 1]);
		a->p = 0;
		if (!(++i < (argc - 1)))
			break ;
		a->next = malloc(sizeof(x_list));
		a = a->next;
	}
	a->next = NULL;
	return (0);
}

int	check_list(x_list *a)
{
	x_list	*t1;
	x_list	*t2;
	int		i1;
	int		i2;

	t1 = a;
	if (a->next == NULL)
		return (0);
	i1 = 0;
	while (t1)
	{
		i2 = 0;
		t2 = a;
		while (t2)
		{
			if (t1->x == t2->x && i1 != i2)
				return (1);
			t2 = t2->next;
			i2++;
		}
		t1 = t1->next;
		i1++;
	}
	return (0);
}

int	free_list(x_list *a)
{
	x_list	*temp;

	while (a)
	{
		temp = a;
		a = a->next;
		free(temp);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	x_list		*a;
	x_list		*b;
	int			strat;

	if (argc < 2)
		return (0);
	a = malloc(sizeof(x_list));
	b = NULL;
	if (fill_list(a, argc, argv, &strat) != 0)
	{
		err();
		free_list(a);
		return (1);
	}
	if (check_list(a) != 0)
	{
		err();
		free_list(a);
		return (1);
	}
	push_swap(&a, &b, strat);
	free_list(a);
	return (1);
}
