/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:09:55 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:09:56 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* count the number of nodes of a list*/
int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*node;

	size = 0;
	node = lst;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}
