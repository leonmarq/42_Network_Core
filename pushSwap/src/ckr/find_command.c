/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:46:24 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/28 13:49:35 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	is_commandwnl(char *command)
{
	if (ft_strncmp(command, "sa\n", 4) == 0
		|| ft_strncmp(command, "sb\n", 4) == 0
		|| ft_strncmp(command, "ss\n", 4) == 0
		|| ft_strncmp(command, "pa\n", 4) == 0
		|| ft_strncmp(command, "pb\n", 4) == 0
		|| ft_strncmp(command, "ra\n", 4) == 0
		|| ft_strncmp(command, "rb\n", 4) == 0
		|| ft_strncmp(command, "rr\n", 4) == 0
		|| ft_strncmp(command, "rra\n", 5) == 0
		|| ft_strncmp(command, "rrb\n", 5) == 0
		|| ft_strncmp(command, "rrr\n", 5) == 0)
		return (1);
	return (0);
}

int	is_commandnonl(char *command)
{
	if (ft_strncmp(command, "sa", 3) == 0
		|| ft_strncmp(command, "sb", 3) == 0
		|| ft_strncmp(command, "ss", 3) == 0
		|| ft_strncmp(command, "pa", 3) == 0
		|| ft_strncmp(command, "pb", 3) == 0
		|| ft_strncmp(command, "ra", 3) == 0
		|| ft_strncmp(command, "rb", 3) == 0
		|| ft_strncmp(command, "rr", 3) == 0
		|| ft_strncmp(command, "rra", 4) == 0
		|| ft_strncmp(command, "rrb", 4) == 0
		|| ft_strncmp(command, "rrr", 4) == 0)
		return (1);
	return (0);
}
