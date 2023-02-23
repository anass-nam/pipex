#include "pipex.h"

static char    **get_env_paths(char **env)
{
    while (*env)
    {
        if (!ft_strncmp(*env, "PATH=", 5))
            return (ft_split((*env) + 5, ':'));
        env++;
    }
    return NULL;
}

int main(int ac, char const **av, char **env)
{
    char    **paths;
    t_pip   *cmd1;

    if (ac != 3)
        return 1;
    redirect(*(av + 1), 'i');
    paths = get_env_paths(env);
    cmd1 = get_cmd(*(av + 2), paths);
    if (execve(cmd1->cmd_fullpath, cmd1->cmd, NULL) == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
