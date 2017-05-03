# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgutniko <lgutniko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/27 12:03:56 by lgutniko          #+#    #+#              #
#    Updated: 2017/05/03 14:10:50 by iiliuk           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_db
SRC		= ft_db.c del_by_num.c del_by_keyword.c append.c search.c print.c \
		edit_by_num.c edit_by_keyword.c
FLAG	= -Wall -Wextra -Werror
OBJ		= $(SRC:.c=.o)

GR=\033[0;32m
RD=\033[0;31m
NC=\033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) -c $(SRC)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "${GR}ft_db is ready to run${NC}"

clean:
	@/bin/rm -f $(OBJ)
	@echo "${RD}object files were deleted${NC}"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "${RD}all the files were deleted${NC}"

re: fclean all
