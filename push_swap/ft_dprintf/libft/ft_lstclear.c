/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:29:04 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/12 10:29:04 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*walk;

	if (!lst || !del)
		return ;
	walk = *lst;
	while (walk != NULL)
	{
		temp = walk;
		walk = walk->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
