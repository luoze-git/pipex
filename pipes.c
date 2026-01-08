/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:32 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/08 13:46:33 by luozguo          ###   ########.fr       */
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

	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		fatal_parent_prefork(parent, "malloc pipes");
	parent->pipes = pipes;
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			fatal_parent_prefork(parent, "pipe");
		i++;
	}
}
