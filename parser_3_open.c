#include "pipex.h"

void open_input(t_parsed *p, char **argv)
{
	if (p->here_doc)
		p->in_fd = here_doc_pipe(p->limiter);
	else
		p->in_fd = open(argv[p->cmd_start_idx - 1], O_RDONLY);
	if (p->in_fd < 0)
		fatal_parent_prefork("open input file");
}

void open_output(t_parsed *p, int argc, char **argv)
{
	int flags;

	flags = O_CREAT | O_WRONLY;
	if (p->here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	p->out_fd = open(argv[argc - 1], flags, 0644);
	if (p->out_fd < 0)
		fatal_parent_prefork(argv[argc - 1]);
}
