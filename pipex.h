#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_cmd
{
	char const	*fullpath;
	char const	**args;
}   t_cmd;

typedef struct	s_pipex
{
	t_cmd	**cmd;
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	pid_t	pid[2];
}	t_pipex;

typedef unsigned char t_byte; // unsigned byte (8 bits)

# define INFILE 0x01      // close infile fd
# define OUTFILE 0x02     // close outfile fd
# define PIPE 0x04    // close pipe fds
# define CMDS 0x08      // free cmds fullpath and args
# define PROC_SUCCESS 0x010   // exit(EXIT_SUCCESS)
# define PROC_FAILURE 0x020   // exit(EXIT_FAILURE)
# define ALL_SUCCESS 0x0B   // release all used ressourses (mem, fds)
# define ALL_FAILURE 0x02F   // release all used ressourses (mem, fds) and exit(EXIT_FAILURE)

# define FAIL -1

# define ERENV "pipex: cannot access Environment variables"
# define ERPATH "pipex: PATH variable not found"
# define ERHEAP "malloc: Failed to allocate the required memory"

t_cmd	**parse_cmds(char const **av, char const **path);
// utils
void    console_err(char *err_holder, ...);
void	free_2d(void **ptr);
void    free_cmds(t_cmd **cmd, int i);
void    release(t_pipex *pipex, t_byte option);

#endif