# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorin <clorin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 09:43:04 by clorin            #+#    #+#              #
#    Updated: 2021/01/04 10:31:21 by clorin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = Cub3D

#	Sources

SRC			=	srcs/main.c srcs/images.c srcs/map.c srcs/player.c srcs/window.c srcs/tools.c srcs/setup.c \
				srcs/parse.c srcs/graphics.c srcs/game.c srcs/check_map.c srcs/keyboard.c srcs/render.c \
				srcs/map_utils.c srcs/raycasting.c

CC			=	clang

FLAGS		= -Werror -Wextra -Wall

HEADER		= -I includes/

OBJ 		= $(SRC:.c=.o)

all : $(NAME)

.c.o:
			@${CC} ${FLAGS} ${HEADER} -c $< -o ${<:.c=.o}
			@echo "compilation : "$< "\033[32mok\033[0m"

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME) -L libft/ -lft -L./minilibx -lmlx -framework OpenGL -framework Appkit
	#@$(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME) -L libft/ -lft -L./minilibx -lmlx -lXext -lX11 -lm -lz 
	@echo "création de Cub3D : \033[32mok\033[0m"

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

.PHONY: all clean fclean re
