#include "pipex.h"

int    pipex_exec(t_cmd *cmd, int fd1, int fd2, int fd3)
{
    int in;
    int out;

    if (close(fd3) == FAIL)
        return (FAIL);
    in = dup2(fd1, STDIN_FILENO);
    if (close(fd1) == FAIL)
        return (FAIL);
    out = dup2(fd2, STDOUT_FILENO);
    if (close(fd2) == FAIL)
        return (FAIL);
    if (in == FAIL || out == FAIL)
        return (FAIL);
    return (execve(cmd->fullpath, cmd->args, NULL));
}

int main(int argc, char const *argv[], char const **env)
{
    t_pipex *pipex;
    int     fd[2];
    pid_t   pid[2];

    pipex = parcer(argc, argv, env);
    if (pipe(fd) == FAIL)
        safe_exit(EXIT_FAILURE, pipex, NULL);
    pid[0] = fork();
    if (pid[0] == FAIL)
        safe_exit(EXIT_FAILURE, pipex, fd);
    if (pid[0] == 0)
        if (pipex_exec(pipex->cmd[0], pipex->infile, fd[1], fd[0]) == FAIL)
            safe_exit(EXIT_FAILURE, pipex, fd);
    pid[1] = fork();
    if (pid[1] == FAIL)
        safe_exit(EXIT_FAILURE, pipex, fd);
    if (pid[1] == 0 && pid[0])
        if (pipex_exec(pipex->cmd[1], fd[0], pipex->outfile, fd[1]) == FAIL)
            safe_exit(EXIT_FAILURE, pipex, fd);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
    safe_exit(EXIT_SUCCESS, pipex, NULL);
    return 0;
}
