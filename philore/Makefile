# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 13:42:23 by seayeo            #+#    #+#              #
#    Updated: 2024/12/06 15:41:38 by seayeo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH = src/
SRC = 	philo.c \
		getandset.c \
		init.c \
		philo_status.c \
		process.c \
		utils.c \
		utils2.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:.c=.o)
OBJ_PATH = objs/
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f
	
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
all: $(NAME)

clean:
	$(RM) $(OBJS) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re