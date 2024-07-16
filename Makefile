# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 13:42:23 by seayeo            #+#    #+#              #
#    Updated: 2024/07/16 13:46:27 by seayeo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c \
		philo.c \
		utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re