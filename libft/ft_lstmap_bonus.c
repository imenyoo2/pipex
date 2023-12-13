/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:26:08 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/04 13:47:26 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_list(t_list *lst, t_list *head,
		void *(*f)(void *), void (*del)(void *))
{
	void	*modcontent;
	t_list	*tmp;
	t_list	*holder;

	holder = head;
	while (lst)
	{
		modcontent = f(lst->content);
		tmp = ft_lstnew(modcontent);
		if (tmp == NULL)
		{
			ft_lstclear(&head, del);
			free(modcontent);
			return (0);
		}
		holder->next = tmp;
		holder = tmp;
		lst = lst->next;
	}
	return (1);
}

// TODO: not tested
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*modcontent;

	if (!lst || !f || !del)
		return (NULL);
	modcontent = f(lst->content);
	head = ft_lstnew(modcontent);
	if (head == NULL)
	{
		free(modcontent);
		return (NULL);
	}
	lst = lst->next;
	if (!fill_list(lst, head, f, del))
		return (NULL);
	return (head);
}
