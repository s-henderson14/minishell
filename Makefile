# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sean <sean@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 10:55:55 by shenders          #+#    #+#              #
#    Updated: 2023/07/06 12:44:52 by gozturk       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

USER			:=	$(shell whoami)

#codam setting
#export RL_LIB	:= -L/Users/$(USER)/.brew/opt/readline/lib
#export RL_INC	:= -I/Users/$(USER)/.brew/opt/readline/include

#home setting
export LDFLAGS="-L/usr/local/opt/readline/lib"
export CPPFLAGS="-I/usr/local/opt/readline/include"

NAME	:= minishell
CFLAGS	:= -g -Wall -Wextra -Werror
LIBS	:= -lreadline
LIBFT	:= libft/libft.a
HEADERS := -I libft -I include 
SRCS 	:=	src/main.c \
			src/test.c \
			src/env/env.c \
			src/env/env_utils.c \
			src/env/env_utils_2.c \
			src/builtin/mini_cd.c \
			src/builtin/mini_echo.c \
			src/builtin/mini_pwd.c \
			src/builtin/mini_env.c \
			src/builtin/mini_exit.c \
			src/builtin/mini_unset.c \
			src/builtin/mini_export.c \
			src/builtin/builtin_utils.c \
			src/execution/redirections.c \
			src/execution/heredoc.c \
			src/utils/utils.c

#SRCS	:= ${SRCS:%=./src/%}
OBJS	:= ${SRCS:.c=.o}
all:  libft $(NAME)
	@echo $(RL_INC)

libft:
	$(MAKE) -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<  && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(HEADERS) $(LIBS) $(RL_LIB) -o $(NAME)

.PHONY: libft fclean clean re

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
