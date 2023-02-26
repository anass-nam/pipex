#include "pipex.h"

static void is_failed(int indicator, char *func)
{
    if (indicator < 0)
    {
        perror(func);
        exit(EXIT_FAILURE);
    }
}

static char **get_env_paths(char **env)
{
    char    **paths;

    paths = NULL;
    while (env && *env)
    {
        if (!ft_strncmp(*env, "PATH=", 5))
        {
            env[0][3] = '.';
            env[0][4] = ':';
            paths = ft_split((*env) + 3, ':');
            break ;
        }
        env++;
    }
    if (!paths)
    {
        ft_putendl_fd(ERPATH, 2);
        exit(EXIT_FAILURE);
    }
    return paths;
}

static  void run_first(t_cmd *cmd, int pipe_fd[2], const char *file)
{
    int fd;
    printf("%s\n", file);
    fd = open(file, O_RDONLY, ROMODE);
    is_failed(fd, "open");
    is_failed(dup2(fd, STDIN_FILENO), "dup2");
    is_failed(close(fd), "close");
    is_failed(close(pipe_fd[0]), "close");
    is_failed(dup2(pipe_fd[1], STDOUT_FILENO), "dup2");
    is_failed(close(pipe_fd[1]), "close");
    is_failed(execve(cmd->fullpath, cmd->args, NULL), "execve");
}

static  void run_second(t_cmd *cmd, int pipe_fd[2], const char *file)
{
    int fd;

    fd = open(file, O_RDWR | O_CREAT, RWMODE);
    is_failed(fd, "open");
    is_failed(dup2(fd, STDOUT_FILENO), "dup2");
    is_failed(close(fd), "close");
    is_failed(close(pipe_fd[1]), "close");
    is_failed(dup2(pipe_fd[0], STDIN_FILENO), "dup2");
    is_failed(close(pipe_fd[0]), "close");
    is_failed(execve(cmd->fullpath, cmd->args, NULL), "execve");
}

int main(int ac, char const **av, char **env)
{
    char    **paths;
    t_cmd   *cmd;
    pid_t   pid1;
    pid_t   pid2;
    int     pipe_fd[2];

    if (ac != 5)
        return 1;
    paths = get_env_paths(env);
    is_failed(pipe(pipe_fd), "pipe");
    pid1 = fork();
    is_failed(pid1, "fork");
    if (pid1 == 0)
    {
        cmd = get_cmd(av[2], paths);
        run_first(cmd, pipe_fd, av[1]);
    }
    pid2 = fork();
    is_failed(pid2, "fork");
    if (pid2 == 0 && pid1)
    {
        cmd = get_cmd(av[3], paths);
        run_second(cmd, pipe_fd, av[4]);
    }
    is_failed(close(pipe_fd[0]), "close");
    is_failed(close(pipe_fd[1]), "close");
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}


/*
fd[0] read;
fd[1] write;




*/