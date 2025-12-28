/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:15:26 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:18:12 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* notice:
	1. returned length is the literal string length without the null terminator.
	2. if dst and src overlap, then the behavior is undefined.
	3. if len <= dstsize, then the user know the output is truncated.
*/

// same category as strlcpy;
// one of the target is to NULL-terminate dst,which may not have it.

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = 0;
	srclen = 0;
	while (dstlen < dstsize && dst[dstlen])
		dstlen++;
	while (src[srclen] && dstsize > srclen + dstlen + 1)
	{
		dst[srclen + dstlen] = src[srclen];
		srclen++;
	}
	if (dstsize > dstlen)
		dst[srclen + dstlen] = '\0';
	while (src[srclen])
		srclen++;
	return (srclen + dstlen);
}
