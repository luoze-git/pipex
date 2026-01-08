/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:46:29 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/08 13:46:30 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc_pipe(char *limiter, t_parent *parent)
{
	int		fd[2];
	char	*line;
	size_t	lim_len;

	if (pipe(fd) < 0)
		fatal_parent_prefork(parent, "pipe");
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

void	open_input(t_parsed *p, char **argv, t_parent *parent)
{
	if (p->here_doc)
		p->in_fd = here_doc_pipe(p->limiter, parent);
	else
		p->in_fd = open(argv[p->cmd_start_idx - 1], O_RDONLY);
	if (p->in_fd < 0)
		fatal_parent_prefork(parent, "open input file");
}

void	open_output(t_parsed *p, int argc, char **argv, t_parent *parent)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if (p->here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	p->out_fd = open(argv[argc - 1], flags, 0644);
	if (p->out_fd < 0)
		fatal_parent_prefork(parent, argv[argc - 1]);
}
