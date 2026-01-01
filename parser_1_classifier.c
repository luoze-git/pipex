#include "pipex.h"

/*`
./pipex file1 cmd1 cmd2 file2

 0        1     2    3    4
< file1 cmd1 | cmd2 > file2



./pipex here_doc LIMITER cmd cmd1 file

0			 1        2    3    4 	5

cmd << LIMITER | cmd1 >> file
*/

// allow cmd_path to be NULL if not found. Check for that before execve

void	get_input_pattern(t_parsed *p, int argc, char **argv)
{
	if (argc < 5)
		fatal_parent_prefork("invalid arguments");
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			fatal_parent_prefork("invalid arguments");
		p->here_doc = 1;
		p->limiter = argv[2];
		p->cmd_start_idx = 3;
		p->cmd_count = argc - p->cmd_start_idx - 1;
		return ;
	}
	p->here_doc = 0;
	p->limiter = NULL;
	p->cmd_start_idx = 2;
	p->cmd_count = argc - p->cmd_start_idx - 1;
}

static void	init_parsed(t_parsed *p)
{
	p->in_fd = -1;
	p->out_fd = -1;
	p->cmd_count = 0;
	p->cmd_start_idx = 0;
	p->cmds = NULL;
	p->here_doc = 0;
	p->limiter = NULL;
}

t_parsed	*parse_input(int argc, char **argv, char **envp)
{
	t_parsed	*p;

	p = malloc(sizeof(t_parsed));
	if (!p)
		fatal_parent_prefork("malloc parsed");
	init_parsed(p);
	get_input_pattern(p, argc, argv);
	open_input(p, argv);
	parse_multi_cmds(p, argv, envp);
	open_output(p, argc, argv);
	return (p);
}
