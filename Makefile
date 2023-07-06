# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sean <sean@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 10:55:55 by shenders          #+#    #+#              #
#    Updated: 2023/06/25 22:44:48 by sean             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME	:= minishell
CFLAGS	:= -g -Wall -Wextra -Werror -lreadline
LIBFT	:= libft/libft.a
HEADERS := -I libft -I include 
SRCS 	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}
all:  libft $(NAME)

libft:
	$(MAKE) -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(HEADERS) -o $(NAME)

.PHONY: libft fclean clean re

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
