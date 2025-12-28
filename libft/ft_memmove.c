/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:10:26 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:17:14 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// memmove : Non-destructive manner in terms of the data stored in src

static void	ft_backward_cp(unsigned char *dst, const unsigned char *src,
		size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[len - i - 1] = src[len - i - 1];
		i++;
	}
}

static void	ft_forward_cp(unsigned char *dst, const unsigned char *src,
		size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

// check the overlap of memory
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src = (const unsigned char *)src;

	ptr_dst = (unsigned char *)dst;
	if (ptr_dst == ptr_src || len == 0)
		return (dst);
	if (ptr_dst < ptr_src || ptr_src + len <= ptr_dst)
		ft_forward_cp(ptr_dst, ptr_src, len);
	else
		ft_backward_cp(ptr_dst, ptr_src, len);
	return (dst);
}
