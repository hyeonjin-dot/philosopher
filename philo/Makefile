# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/14 14:35:12 by hyejung           #+#    #+#              #
#    Updated: 2021/11/06 18:35:50 by hyejung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	main.c\
				tool.c\
				init.c\
				start.c

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
OBJS        = 	$(SRCS:.c=.o)

$(NAME) :	$(OBJS)
	$(CC) $(CFLAGS) -lpthread $(OBJS) -o $(NAME)

all		:	$(NAME)

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean $(NAME)

.PHONY	:	all clean fclean re
