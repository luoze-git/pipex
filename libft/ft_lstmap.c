/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:09:44 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:09:45 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init_vars(t_list **out, t_list **tail, t_list **node, void **cnt)
{
	*out = NULL;
	*tail = NULL;
	*node = NULL;
	*cnt = NULL;
}
/* creates a new list with new content (original untouched).*/
/*  1. conditionals in the loop to specify the header(out).
	2. del() the content only half-way inside the new node.*/

static void	ft_append_n_update(t_list **out, t_list **tail, t_list **node,
		t_list **lst)
{
	if (!(*out))
		*out = *node;
	else
		(*tail)->next = *node;
	*tail = *node;
	*lst = (*lst)->next;
}

/*node alloc fail. del content for node on building,
	clear all nodes already linked*/
static void	*ft_lstclean(t_list **out, void *cnt, void (*del)(void *))
{
	if (cnt)
		del(cnt);
	ft_lstclear(out, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*out;
	t_list	*tail;
	t_list	*node;
	void	*cnt;

	if (!f || !del)
		return (NULL);
	ft_init_vars(&out, &tail, &node, &cnt);
	while (lst)
	{
		cnt = f(lst->content);
		if (!cnt)
		{
			ft_lstclear(&out, del);
			return (NULL);
		}
		node = ft_lstnew(cnt);
		if (!node)
			return (ft_lstclean(&out, cnt, del));
		ft_append_n_update(&out, &tail, &node, &lst);
	}
	return (out);
}
