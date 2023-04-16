#include "pipex.h"

static char	**get_env_path(char **env)
{
	char	**path;

	if (env == NULL)
		return (console_err("$\n", ERENV), NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			env[3] = '.';
			env[4] = ':';
			path = ft_split((*env) + 3, ':');
			if (path == NULL)
				return (console_err("$\n", ERHEAP), NULL);
			return (path);
		}
		env++;
	}
	return (console_err("$\n", ERPATH), NULL);
}

static void	pipex_init(t_pipex *pipex, char const **av, char **env)
{
	char const	**path;

	if (pipe(pipex->pipe_fd) == FAIL)
		exit(EXIT_FAILURE);
	path = get_env_path(env);
	if (path == NULL)
		release(pipex, PIPE | PROC_FAILURE);
	pipex->cmd = parse_cmds(av + 1, path);
	free_2d(path);
	if (pipex->cmd == NULL)
		release(pipex, PIPE | PROC_FAILURE);
	pipex->infile = open(av[0], O_RDONLY);
	if (pipex->infile == FAIL)
	{
		perror("open");
		release(pipex, PIPE | CMDS | PROC_FAILURE);
	}
	pipex->outfile = open(av[3], O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (pipex->outfile == FAIL)
	{
		perror("open");
		release(pipex, PIPE | CMDS | INFILE | PROC_FAILURE);
	}
}

int	main(int ac, char const **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
		exit(EXIT_FAILURE);
	pipex_init(&pipex, av + 1, env);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == -1)
		release(&pipex, ALL_FAILURE);
	if (pipex.pid[0] == 0)
		pipex_exec();
	pipex.pid[1] = fork();
	if (pipex.pid[1] == -1)
		release(&pipex, ALL_FAILURE);
	if (pipex.pid[1] == 0 && pipex.pid[0] != 0)
		pipex_exec();
	release(&pipex, PIPE);
	waitpid(pipex.pid[0], NULL, 0);
	waitpid(pipex.pid[1], NULL, 0);
	release(&pipex, ALL_SUCCESS);
	return 0;
}
