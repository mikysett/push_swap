# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msessa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 11:32:44 by msessa            #+#    #+#              #
#    Updated: 2021/06/04 16:46:27 by msessa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	--quiet

WHT	= \033[0;37m
BLK	= \033[0;30m
RED	= \033[0;31m
YEL	= \033[0;33m
BLU	= \033[0;34m
GRN	= \033[0;32m

NAME	=	push_swap

FAST	=	

LIBFT	=	libft/libft

HEADERS	=	headers

DIR_S	=	srcs

DIR_O	=	obj

# Using wildcards: $(shell find $(DIR_S) -name *.c)
SRCS	:=	$(shell find $(DIR_S) -name *.c)

OBJS	:= $(SRCS:%.c=$(DIR_O)/%.o)

SUB_DIR_O := $(shell find $(DIR_S) -type d)
SUB_DIR_O := $(SUB_DIR_O:%=$(DIR_O)/%)

# Using wildcards: $(shell find $(HEADERS) -name *.h)
DEPS	=	$(shell find $(HEADERS) -name *.h)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -fsanitize=address

INCLUDES	= -I $(HEADERS)

LIBS	=	-L./$(LIBFT) -lft

RM		=	rm -f

$(DIR_O)/%.o: %.c
			@mkdir -p $(DIR_O)
			@mkdir -p $(SUB_DIR_O)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME):	$(DEPS) $(OBJS)
			@make $(FAST)bonus -C $(LIBFT)
			@make $(FAST) -C ft_checker
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)
			printf "$(WHT)[$(GRN)$(NAME) COMPILED$(WHT)]\n"

all:		$(NAME)

fast:		CFLAGS += -O3
fast:		FAST = fast
fast:		all
			printf "$(WHT)[$(GRN)$(NAME) --> OPTIMIZATION FLAG ACTIVE (-O3)$(WHT)]\n"

miniclean:
			$(RM) $(OBJS)
			$(RM) $(BOBJS)
			printf "$(WHT)[$(YEL)$(NAME) OBJS REMOVED$(WHT)]\n"
			@make clean -C ft_checker

clean:		miniclean
			@make clean -C $(LIBFT)

fclean:		clean
			$(RM) $(NAME)
			printf "$(WHT)[$(YEL)$(NAME) BINARIES REMOVED$(WHT)]\n"
			@make fclean -C $(LIBFT)
			@make fclean -C ft_checker

re:			fclean all

.PHONY:		all fast clean fclean miniclean re
