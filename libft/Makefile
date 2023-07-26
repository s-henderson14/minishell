# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: gozturk <gozturk@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/11 18:39:50 by gozturk       #+#    #+#                  #
#    Updated: 2022/11/07 18:05:39 by gozturk       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c \
			ft_bzero.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c 

SRCB = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
		   	ft_lstmap_bonus.c	

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

ifdef WITH_BONUS
SRC += $(SRCB)
endif

all : $(NAME)

bonus :
	$(MAKE) WITH_BONUS=1
#bonus : $(OBJ) $(OBJB)
#			ar rc $(NAME) $^

$(NAME) : $(OBJ) 
			ar rc $@ $? 

clean :
			rm -f $(OBJ) $(OBJB)

fclean :	clean
			rm -f $(NAME)

re : fclean all

.PHONY = all clean fclean re bonus

