/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:36:17 by leon              #+#    #+#             */
/*   Updated: 2022/04/08 15:36:19 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_median_end2(t_list *a, int size, int med, int k)
{
	int		i;
	int		t;
	t_list	*temp;

	temp = a;
	while (temp && temp->p == k)
	{
		if (temp->x < med)
			med = temp->x;
		temp = temp->next;
	}
	i = -1;
	while (++i < size)
	{
		t = med;
		med = INT32_MAX;
		temp = a;
		while (temp && temp->p == k)
		{
			if (temp->x < med && temp->x > t)
				med = temp->x;
			temp = temp->next;
		}
	}
	return (med);
}

int	find_median_end(t_list *a)
{
	int		med;
	int		size;
	int		k;
	t_list	*temp;

	temp = a;
	while (temp->next)
		temp = temp->next;
	k = temp->p;
	size = 0;
	temp = a;
	while (a->p != k)
		a = a->next;
	temp = a;
	while (temp && temp->p == k)
	{
		size++;
		temp = temp->next;
	}
	size = size / 2;
	med = INT32_MAX;
	med = find_median_end2(a, size, med, k);
	return (med);
}

int	find_median2(t_list *a, int size, int med, int k)
{
	int		i;
	int		t;
	t_list	*temp;

	temp = a;
	while (temp && temp->p == k)
	{
		if (temp->x < med)
			med = temp->x;
		temp = temp->next;
	}
	i = -1;
	while (++i < size)
	{
		t = med;
		med = INT32_MAX;
		temp = a;
		while (temp && temp->p == k)
		{
			if (temp->x < med && temp->x > t)
				med = temp->x;
			temp = temp->next;
		}
	}
	return (med);
}

int	find_median(t_list *a)
{
	int		med;
	int		size;
	int		k;
	t_list	*temp;

	temp = a;
	k = a->p;
	size = 0;
	while (temp && temp->p == k)
	{
		size++;
		temp = temp->next;
	}
	size = size / 2;
	med = INT32_MAX;
	med = find_median2(a, size, med, k);
	return (med);
}
