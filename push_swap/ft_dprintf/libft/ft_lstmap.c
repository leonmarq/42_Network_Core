/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonmarq <leonmarq@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:29:23 by leonmarq          #+#    #+#             */
/*   Updated: 2026/03/19 12:01:47 by leonmarq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*n;
	void	*c;

	if (!f)
		return (NULL);
	r = NULL;
	while (lst)
	{
		c = f(lst->content);
		n = ft_lstnew(c);
		if (!n)
		{
			if (del)
				del(c);
			ft_lstclear(&r, del);
			return (NULL);
		}
		ft_lstadd_back(&r, n);
		lst = lst->next;
	}
	return (r);
}
