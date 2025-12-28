/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:12:16 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:12:17 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// memset : set a block of memory to bytes of value.
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	ar;
	size_t			i;

	ptr = (unsigned char *)b;
	ar = c;
	i = 0;
	while (i < len)
	{
		ptr[i] = ar;
		i++;
	}
	return (b);
}
