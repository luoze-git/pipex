/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:15:03 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 15:17:36 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_rec(long nl, int fd)
{
	char	ch;

	if (nl >= 10)
		ft_putnbr_rec(nl / 10, fd);
	ch = nl % 10 + '0';
	write(fd, &ch, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nl;

	nl = n;
	if (nl < 0)
	{
		write(fd, "-", 1);
		nl = -nl;
	}
	ft_putnbr_rec(nl, fd);
}
