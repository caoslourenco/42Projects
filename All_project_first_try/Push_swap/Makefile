# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clourenc  <clourenc@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 16:11:06 by clourenc          #+#    #+#              #
#    Updated: 2023/01/13 22:25:27 by clourenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =      push_swap
HEADER =    -I ./include
SRC_DIR =   ./src
OBJ_DIR =	./objects
LIBFT 	=	./libft/libft.a
SRC_FILES =		radix.c utils.c \

CC =		cc -Wall -Wextra -Werror -g3 -O3 

SRC =		$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ =		$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cc $(OBJ) $(LIBFT) $(CFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(OBJ_DIR)
	$(CC) $(HEADER) -c  $< -o $@ 

clean:
	rm -rf $(OBJ_DIR)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re