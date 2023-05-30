# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmohamed <hmohamed@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 18:14:30 by hmohamed          #+#    #+#              #
#    Updated: 2023/03/19 17:22:04 by hmohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c utils.c rout.c extra.c forklock.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

clean:
		rm -f *.o 

fclean: clean
		rm -f philo
		
re: fclean all