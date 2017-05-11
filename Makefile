# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgutniko <lgutniko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/27 12:03:56 by lgutniko          #+#    #+#              #
#    Updated: 2017/05/10 15:58:08 by iiliuk           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_db
SRC		= ft_db.c del_by_num.c del_by_keyword.c append.c search.c print.c \
		edit_by_num.c edit_by_keyword.c rewrite_file.c get_record.c
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

leaks: re
	@osascript -e 'tell application "iTerm2" to activate' -e 'tell application "System Events" to tell process "iTerm2" to keystroke "D" using command down' -e 'tell application "System Events" to tell process "iTerm" to keystroke "while true ; do clear; leaks $(NAME); sleep 2 ; done"' -e 'tell application "System Events" to tell process "iTerm" to key code 52'

clean:
	@/bin/rm -f $(OBJ)
	@echo "${RD}object files were deleted${NC}"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "${RD}all the files were deleted${NC}"

re: fclean all
