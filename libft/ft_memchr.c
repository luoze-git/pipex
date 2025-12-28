/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:09:58 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:09:59 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// search will not stop at '/0'.
// Always use unsigned char for raw memory functions.
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = (const unsigned char *)s;
	unsigned char		uc;
	size_t				i;

	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == uc)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
