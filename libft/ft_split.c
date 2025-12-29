/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:23:43 by luozguo           #+#    #+#             */
/*   Updated: 2025/12/29 16:34:47 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*count one word length. update the iterator k to point to the word*/
static size_t	ft_wordlen(char const *s, char c, size_t *k)
{
	size_t	len;

	len = 0;
	while (s[*k] == c)
		(*k)++;
	while (s[*k + len] && s[*k + len] != c)
		len++;
	return (len);
}

/*count how many words sep by char c*/
static size_t	ft_wordcount(char const *s, char c)
{
	size_t	num_words;
	size_t	i;
	int		met_delim;

	num_words = 0;
	met_delim = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && met_delim == 1)
		{
			num_words++;
			met_delim = 0;
		}
		else if (s[i] == c)
			met_delim = 1;
		i++;
	}
	return (num_words);
}

/*free the allocated memory when things go wrong*/
static char	**error_free_split(char **ptr, size_t n)
{
	size_t	offset;

	offset = 0;
	while (offset < n)
	{
		free(ptr[offset]);
		offset++;
	}
	free(ptr);
	return (NULL);
}

static void	ft_init_vars(size_t *num_words, size_t *i, size_t *k, char ***ptr)
{
	*k = 0;
	*i = 0;
	*ptr = NULL;
	*num_words = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	num_words;
	size_t	i;
	size_t	k;
	size_t	len;
	char	**ptr;

	if (!s)
		return (NULL);
	ft_init_vars(&num_words, &i, &k, &ptr);
	num_words = ft_wordcount(s, c);
	ptr = ft_calloc(num_words + 1, sizeof(*ptr));
	if (!ptr)
		return (NULL);
	while (i < num_words)
	{
		len = ft_wordlen(s, c, &k);
		ptr[i] = ft_substr(s, k, len);
		if (!ptr[i])
			return (error_free_split(ptr, i));
		k = len + k;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
