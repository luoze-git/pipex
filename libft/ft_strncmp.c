/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:15:45 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:15:50 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// factor affecting corner case: size_t n == 0.
// 1. if size_t n == 0, it shouldn't compare at all.
// 2. if i == n, then also 0.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
