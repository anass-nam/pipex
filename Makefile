pipex:
	cc -g -Wall -Wextra -Werror *.c -o pipex -lft
clean:
	rm -f pipex
fclean: clean
	rm -f *.txt