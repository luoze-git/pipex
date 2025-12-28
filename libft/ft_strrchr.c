/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:16:12 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:16:15 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*find = NULL;
	char		ch;

	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			find = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)find);
}
