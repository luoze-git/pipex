# include "pipex.h"


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
