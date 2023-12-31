# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sean <sean@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 10:55:55 by shenders          #+#    #+#              #
#    Updated: 2023/07/06 14:07:28 by shenders      ########   odam.nl          #
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
				src/test/test.c \
				src/test/test_redirection.c \
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
				src/execute/redirections.c \
				src/execute/heredoc.c \
				src/execute/execute.c \
				src/execute/handle_pipes.c \
				src/execute/execute_utils.c \
				src/utils/utils.c \
				src/utils/utils_list.c \
				src/error_syntax/syntax_check.c \
				src/expansion/double_quotation.c \
				src/expansion/expand_dollar_sign.c \
				src/parser/create_cmds_utils.c \
				src/parser/create_cmds.c \
				src/parser/init_redirection.c \
				src/parser/parser.c \
				src/signals/signals.c \
				src/tokeniser/tokeniser_lst_utils.c \
				src/tokeniser/tokeniser_utils.c \
				src/tokeniser/tokeniser.c

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
