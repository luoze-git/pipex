/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:15:30 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:18:14 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy the src string to dst. output the length of the trying-to-create,
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	to_copy;

	srclen = 0;
	if (dstsize > 0)
		to_copy = dstsize - 1;
	else
		to_copy = 0;
	while (to_copy > 0 && src[srclen])
	{
		dst[srclen] = src[srclen];
		srclen++;
		to_copy--;
	}
	if (dstsize > 0)
		dst[srclen] = '\0';
	while (src[srclen])
		srclen++;
	return (srclen);
}
