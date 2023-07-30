# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 09:32:15 by rjobert           #+#    #+#              #
#    Updated: 2023/07/26 09:32:17 by rjobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = CC

FLAGS = -Wall -Werror -Wextra -MMD -I/.
SRC =  pipe.c env_parsing.c utils.c split_quotes.c
OBJS = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
NAME = pipex

all: $(LIBFT) $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
 
clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME)
	

re: fclean all

.phony: clean re all fclean

