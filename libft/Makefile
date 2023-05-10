# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anammal <anammal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 13:08:18 by anammal           #+#    #+#              #
#    Updated: 2022/10/09 13:08:18 by anammal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC =	$(shell ls ft_*.c | grep -v "bonus.c")
BSRC =	$(shell ls ft_*_bonus.c)
CFLAGS += -Wall -Wextra -Werror
OBJS = $(SRC:.c=.o)
BOBJS = $(BSRC:.c=.o)

all: $(NAME)
	@echo "ALL functions are done!"

$(NAME): $(OBJS)
	@ar rcs $@ $(OBJS)

bonus: $(BOBJS)
	@echo "ALL bonus functions are done!"
	@ar rcs $(NAME) $(BOBJS)

%.o: %.c $(NAME:.a=.h)
	@echo Compiling: $< ... Done!
	@cc $(CFLAGS) -c $< \

clean:
	@echo Cleaned
	@rm -f $(OBJS)
	@rm -f $(BOBJS)

fclean: clean
	@echo Fully cleaned
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re