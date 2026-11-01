/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 17:34:15 by leonmarq          #+#    #+#             */
/*   Updated: 2026/06/27 08:08:32 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static
int	check_arg(char *s)
{
	int	i;

	if (*s == '0' && !*(s + 1))
		return (0);
	i = 0;
	if (s[i] < '1' || s[i] > '9')
		return (1);
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		if (i > 9)
			return (1);
	}
	return (0);
}

int	check_args(char *argv[], int argc)
{
	int	i;

	i = 1;
	while (i < (argc - 1))
	{
		if (check_arg(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
