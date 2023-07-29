# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 18:02:44 by rjobert           #+#    #+#              #
#    Updated: 2023/05/14 17:39:34 by rjobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -I/.

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	  ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	  ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	  ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_itoa.c

OBJS = $(SRC:.c=.o)
DEPS =$(SRC:.c=.d)
NAME = libft.a

all : $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS)  $< -o $@

fclean: clean
	rm -rf $(NAME)

clean:
	rm -f $(OBJS) $(DEPS)

re: fclean all

.PHONY: fclean clean re all 
