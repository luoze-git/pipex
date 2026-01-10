/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:32 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/10 16:42:54 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief malloc and pipe()s setup for all required pipes
/// @param cmd_count
/// @return
void	setup_pipes(int cmd_count, t_parent *parent)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(cmd_count - 1, sizeof(int *));
	if (!pipes)
		fatal_parent_syscall(parent, "malloc");
	parent->pipes = pipes;
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			fatal_parent_syscall(parent, "malloc");
		if (pipe(pipes[i]) == -1)
			fatal_parent_syscall(parent, "pipe");
		i++;
	}
}
