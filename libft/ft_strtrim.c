/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:16:19 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:16:20 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*out;

	out = NULL;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!len)
		return (ft_calloc(1, 1));
	start = 0;
	while (s1[start] && ft_strchr(set, (int)s1[start]))
		start++;
	while (len > start && ft_strchr(set, (int)s1[len - 1]))
		len--;
	if (start <= len)
		out = ft_calloc(len - start + 1, sizeof(*s1));
	else
		return (ft_calloc(1, 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1 + start, len - start + 1);
	return (out);
}
