# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msessa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 11:32:44 by msessa            #+#    #+#              #
#    Updated: 2021/06/24 00:28:09 by msessa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	--quiet

WHT	= \033[0;37m
BLK	= \033[0;30m
RED	= \033[0;31m
YEL	= \033[0;33m
GRN	= \033[0;32m

NAME	=	../checker

FAST	=	

LIBFT	=	../libft/libft

HEADERS	=	headers

DIR_S	=	srcs

DIR_O	=	obj

# Using wildcards: $(shell find $(DIR_S) -name *.c)
SRCS	:=	$(shell find $(DIR_S) -name *.c) \
			../srcs/parser/ft_parser.c \
			../srcs/parser/ft_duplicated_nb.c \
			../srcs/ft_init_data.c \
			../srcs/ft_check_sort.c \
			../srcs/ft_general_util.c

OBJS	:= $(SRCS:%.c=$(DIR_O)/%.o)

SUB_DIR_O := $(shell find $(DIR_S) -type d)
SUB_DIR_O := $(SUB_DIR_O:%=$(DIR_O)/%) \
				srcs/parser

# Using wildcards: $(shell find $(HEADERS) -name *.h)
DEPS	=	$(shell find $(HEADERS) -name *.h)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -fsanitize=address

INCLUDES	= -I $(HEADERS) -I ../headers

LIBS	=	-L./$(LIBFT) -lft

RM		=	rm -f

$(DIR_O)/%.o: %.c
			@mkdir -p $(DIR_O)
			@mkdir -p $(SUB_DIR_O)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME):	$(DEPS) $(OBJS)
			@make $(FAST)bonus -C $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
			printf "$(WHT)[$(GRN)$(NAME) COMPILED$(WHT)]\n"

all:		$(NAME)

fast:		CFLAGS += -O3
fast:		FAST = fast
fast:		all
			printf "$(WHT)[$(GRN)$(NAME) --> OPTIMIZATION FLAG ACTIVE (-O3)$(WHT)]\n"


clean:
			$(RM) $(OBJS)
			printf "$(WHT)[$(YEL)$(NAME) OBJS REMOVED$(WHT)]\n"

fclean:		clean
			$(RM) $(NAME)
			printf "$(WHT)[$(YEL)$(NAME) BINARIES REMOVED$(WHT)]\n"

re:			fclean all

.PHONY:		all fast clean fclean re
