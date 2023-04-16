#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_cmd
{
	char    *fullpath;
	char    **args;
}   t_cmd;

typedef struct	s_pipex
{
	t_cmd	**cmd;
	int		cmd_count;
	int		infile;
	int		outfile;
}	t_pipex;

# define FAIL -1
# define ERENV "pipex: cannot access Environment variables"
# define ERPATH "pipex: PATH variable not found"
# define ERHEAP "malloc: Failed to allocate the required memory"
# define ERINVC "\" command not found"

char	**get_env_path(char const **env);
t_pipex	*parcer(int argc, char const *argv[], char const **env);
//	utils
void	free_2darr(char **ptr);
void    free_cmds(t_cmd **cmd, int i);
void    safe_exit(int status, t_pipex *pipex, int fd[2]);

#endif