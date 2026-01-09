/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:15 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/09 20:40:24 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief used only when a command is not found and exit
/// @param parent
/// @param cmd
void	command_not_found(t_parent *parent, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	close_all_fd_safe(parent);
	cleanup_child(parent);
	exit(127);
}

void	fatal_child_syscall(t_parent *parent, char *msg)
{
	int	errno_save;

	errno_save = errno;
	perror(msg);
	close_all_fd_safe(parent);
	cleanup_child(parent);
	if (errno_save == EACCES)
		exit(126);
	if (errno_save == ENOENT)
		exit(127);
	exit(1);
}

/// @brief Fatal error from syscall (malloc, pipe, open,
///	etc.) in parent before fork
/// @param parent
/// @param msg
void	fatal_parent_syscall(t_parent *parent, char *msg)
{
	perror(msg);
	close_all_fd_safe(parent);
	cleanup_parent(parent);
	exit(1);
}

/// @brief Fatal logical error (invalid arguments, parsing failures,
/// etc.) in parent before fork
/// @param parent
/// @param msg
void	fatal_parent_logical_error(t_parent *parent, char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	close_all_fd_safe(parent);
	cleanup_parent(parent);
	exit(1);
}

/*Children are waited for only to avoid zombies*/
void	fatal_parent_postfork_syscall(t_parent *parent, const char *msg)
{
	perror(msg);
	close_all_fd_safe(parent);
	parent_wait_and_collect(parent);
	cleanup_parent(parent);
	exit(1);
}
