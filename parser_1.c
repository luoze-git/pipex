# include "pipex.h"
/*Parsing in pipex means:

split command strings

resolve command path

build cmd_argv*/

// name file1 cmd1 cmd2 file2

char * ft_strjoin_3_safe(char *a , char * b, char*c)
{
    char *tmp1;
    char *tmp2;
    tmp1 = ft_strjoin(a , b);
    if (!tmp1)
    {
        error_exit();
    }
    tmp2 = ft_strjoin((const char *)tmp1 , c);
    free(tmp1);
    if (!tmp2)
    {
        error_exit();
    }
    return (tmp2);
}


char* search_cmd(char **dirs, char* cmd_name)
{
    int i=0;
    char *path_cm;
    while( dirs[i] != NULL)
    {
        path_cm = ft_strjoin_3_safe (dirs[i] , "/" , cmd_name);
        if(access(path_cm , X_OK) == 0)
            return path_cm;
        free(path_cm);
        i++;
    }
    return (NULL);
}

char *resolve_cmd_path(char *cmd_name, char **envp)
{
    char *path_env = NULL;
    int i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }
    if (!path_env)
        error_exit();
    char **dirs = ft_split(path_env, ':');
    if (!dirs)
        error_exit();
    char *cmd_path;
    cmd_path = search_cmd(dirs , cmd_name );
    if (!cmd_path)
    {
        ft_free_split(dirs);
        error_exit();
    }
    ft_free_split(dirs);
    return(cmd_path);
}

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

