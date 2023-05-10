NAME= pipex
SRC= parser.c pipex.c utils.c
OBJ= $(SRC:.c=.o)
LFTDIR= libft
LIBFT= libft.a
LFT= -I./$(LFTDIR) -L./$(LFTDIR) -lft
CC= gcc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) pipex.h
	@echo Compiling: $@ ... Done!
	@$(CC) $(CFLAGS) $(OBJ) $(LFT) -o $@

$(LIBFT):
	@make -C $(LFTDIR)

%.o: %.c pipex.h
	@echo Compiling: $< ... Done!
	@$(CC) $(CFLAGS) -c $<

clean:
	@echo Cleaned
	@rm -f $(OBJ)

fclean: clean
	@echo Fully cleaned
	@rm -f $(NAME)
	@make fclean -C $(LFTDIR)

re: fclean all

.PHONY: all bonus clean fclean re
