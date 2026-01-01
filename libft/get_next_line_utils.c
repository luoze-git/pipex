/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:09:09 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/01 16:14:47 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief go through param s to find the first new line and return it.
/// @param s
/// @return pointer to 1st new line. NULL if not found.
char	*gnl_has_newline(char *buf_terminated)
{
	int	i;

	i = 0;
	if (!buf_terminated)
		return (NULL);
	while (buf_terminated[i])
	{
		if (buf_terminated[i] == '\n')
			return ((buf_terminated + i));
		i++;
	}
	return (NULL);
}

/// @brief helper of gnl_join to assign the struct t_join_vars
/// @param t
/// @param hd
/// @param tl
/// @param sep
void	ft_init_t_join_vars(t_join_vars *t, char *hd, char *tl, char sep)
{
	t->i = 0;
	t->j = 0;
	t->len_hd = ft_strlen_sep(hd, '\0');
	t->len_tl = ft_strlen_sep(tl, sep);
}

/// @brief join array s2 to malloc-ed s1.
/// @param hd head. is always a full str joint by tl until sep
/// @param tl tail
/// @param sep the char to append at the end of the joint str. if sep is '\0',
///	then no char is appended.
/// @return joined malloc-ed str. NULL if malloc fail or both hd and
/// tl are NULL.
char	*gnl_join(char *hd, char *tl, char sep)
{
	char		*joint;
	t_join_vars	t;

	ft_init_t_join_vars(&t, hd, tl, sep);
	if (t.len_hd + t.len_tl == 0)
		return (NULL);
	joint = malloc(t.len_hd + t.len_tl + 1);
	if (!joint)
		return (NULL);
	while (hd && hd[t.i])
	{
		joint[t.i] = hd[t.i];
		t.i++;
	}
	while (tl && tl[t.j] && tl[t.j] != sep)
		joint[t.i++] = tl[t.j++];
	if (sep != '\0')
		joint[t.i++] = sep;
	joint[t.i] = '\0';
	return (joint);
}

/// checked once for s has multiple new lines.
/// @brief update static array before return. copy from s to stat,
///	copy starting after the first new line. if s is NULL or no new line,
///	stat[0] is set to \0.
void	ft_update_static_array(char *stat, char *s)
{
	int	i;
	int	j;

	if (!s)
	{
		stat[0] = '\0';
		return ;
	}
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	else
	{
		stat[0] = '\0';
		return ;
	}
	j = 0;
	while (s[i] != '\0')
	{
		stat[j++] = s[i++];
	}
	stat[j] = '\0';
}

/// @brief count the length of s until \0 (excluded) or sep (included).
/// @param s
/// @param sep
/// @return length of s excluding the sep. If s is NULL, return 0.
int	ft_strlen_sep(char *s, char sep)
{
	int	i;

	i = 0;
	while (s && s[i] != sep && s[i])
		i++;
	if (s && s[i] == sep && sep != '\0')
		i++;
	return (i);
}
