# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 13:42:23 by seayeo            #+#    #+#              #
#    Updated: 2024/07/18 11:53:47 by seayeo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH = src/
SRC = main.c \
		philo.c \
		utils.c \
		init.c \
		input_check.c \
		safe_functions.c \
		simulation.c \
		synchro.c \
		write.c \
		monitor.c \
		
		
SRCS = $(addprefix $(SRC_PATH), $(SRC))

LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

OBJ_PATH = objs/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

CC = gcc
CFLAGS = 
RM = rm -f
	
all: $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	
$(LIBFT):
	make -C $(LIBFT_PATH)
	
clean:
	$(RM) $(OBJS) $(NAME)
	make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re