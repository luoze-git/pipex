/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:22:32 by luozguo           #+#    #+#             */
/*   Updated: 2025/08/18 16:44:41 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// continuously allocate memory and set them to bytes of zero
// how to detect overflow : use an unequality as condition constraint
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	buffer;

	ptr = NULL;
	buffer = 0;
	if (count && size && count > SIZE_MAX / size)
		return (NULL);
	buffer = count * size;
	ptr = malloc(buffer);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, buffer);
	return (ptr);
}

// #include <stdio.h>
// #include <stdint.h>
// int main()
// {
//     char *ptr1 = ft_calloc(0, 0);
//     char *ptr2 = ft_calloc(0, SIZE_MAX / 2);
//     // *ptr1 = 'A';

//     printf("Pointer1: %p %lu %x\n",
// ptr1, sizeof(*ptr1), (unsigned int)*ptr1);
//     printf("Pointer2: %p %lu %x\n"
// , ptr2, sizeof(*ptr2), (unsigned int)*ptr2);
//     // printf("Pointer2: %p\n", ptr2);

//     // This is a simple C program that does nothing
//     return (0);
// }
