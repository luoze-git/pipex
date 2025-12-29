# include "pipex.h"
/*Parsing in pipex means:

split command strings

resolve command path

build cmd_argv*/

// name file1 cmd1 cmd2 file2

t_parsed * parse_she_line(int argc, char ** argv , char **envp)
{
    t_parsed * parsed;

    if (argc != 5)
        error_exit();
    parsed = malloc(sizeof(t_parsed));
    if (!parsed)
        error_exit();
    parsed->in_fd = open(argv[1], O_RDONLY);
    if (parsed->in_fd == -1)
        error_exit();
    parsed->out_fd = open(argv[4] , O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (parsed->out_fd == -1)
        error_exit();
    parsed->cmd1_argv = ft_split(argv[2], ' ');
    if (!parsed->cmd1_argv || !parsed->cmd1_argv[0])
        error_exit();
    parsed->cmd2_argv = ft_split(argv[3], ' ');
    if (!parsed->cmd2_argv || !parsed->cmd2_argv[0])
        error_exit();
    if (ft_strchr(parsed->cmd1_argv[0], '/'))
    {
        parsed->cmd1_path = ft_strdup(parsed->cmd1_argv[0]);
        if (!parsed->cmd1_path)
            error_exit();
    }
    else
        parsed->cmd1_path = resolve_cmd_path(parsed->cmd1_argv[0] , envp);
    if (ft_strchr(parsed->cmd2_argv[0], '/'))
    {
        parsed->cmd2_path = ft_strdup(parsed->cmd2_argv[0]);
        if (!parsed->cmd2_path)
            error_exit();

    }
    else
        parsed->cmd2_path = resolve_cmd_path(parsed->cmd2_argv[0], envp);
    return (parsed);
}

