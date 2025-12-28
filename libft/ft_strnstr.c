/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:16:08 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:16:09 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	needle is null-terminated; haystack might not.
	the stop condition would be either
	condition is met : len characters are searched or met a '\0'
	so it's not that a function should never segfault,
		but it should never segfault
	when the user is using it correctly. */

static void	ft_init_vars(size_t *nlen, size_t *i, size_t *j)
{
	*j = 0;
	*i = 0;
	*nlen = 0;
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	ft_init_vars(&nlen, &i, &j);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (needle[nlen])
		nlen++;
	while (haystack[i] && i + nlen <= len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] == needle[j] && haystack[i + j])
				j++;
			if (j == nlen)
				return ((char *)(haystack + i));
			if (haystack[i + j] == '\0')
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
