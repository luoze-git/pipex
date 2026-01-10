/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:41 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/10 16:09:40 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_status_to_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

int	parent_wait_and_collect(t_parent *parent)
{
	int	i;
	int	status;
	int	last_exit_code;

	i = 0;
	last_exit_code = 1;
	while (i < parent->spawned)
	{
		waitpid(parent->pids[i], &status, 0);
		if (i == parent->spawned - 1)
			last_exit_code = wait_status_to_exit_code(status);
		i++;
	}
	if (parent->redir_failed)
		return (1);
	return (last_exit_code);
}
