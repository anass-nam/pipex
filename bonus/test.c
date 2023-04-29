#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

void	run(int i)
{
	static int stat;
	pid_t pid;

	if (stat == i)
	{
		pid = fork();
		if (pid == 0)
			printf("pid[%d] == %d\n", i, getpid());
		else
			stat++;
	}

}

int main(void)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		run(i);
		i++;
	}
	wait(NULL);
	return 0;
}
