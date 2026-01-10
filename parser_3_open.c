/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:29 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/10 16:08:16 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc_pipe(char *limiter, t_parent *parent)
{
	int		fd[2];
	char	*line;
	size_t	lim_len;

	if (pipe(fd) < 0)
		fatal_parent_syscall(parent, "pipe");
	lim_len = ft_strlen(limiter);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	open_infile_fd(t_parsed *p, char **argv, t_parent *parent)
{
	if (p->here_doc)
		p->infile_fd = here_doc_pipe(p->limiter, parent);
	else
		p->infile_fd = open(argv[p->cmd_start_idx - 1], O_RDONLY);
	if (p->infile_fd < 0)
	{
		perror(argv[p->cmd_start_idx - 1]);
		p->infile_fd = open("/dev/null", O_RDONLY);
	}
}

void	open_outfile_fd(t_parsed *p, int argc, char **argv, t_parent *parent)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if (p->here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	p->outfile_fd = open(argv[argc - 1], flags, 0644);
	if (p->outfile_fd < 0)
	{
		p->outfile_fd_errno = errno;
		parent->redir_failed = 1;
	}
}
