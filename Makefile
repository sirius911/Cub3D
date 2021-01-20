# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorin <clorin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 09:43:04 by clorin            #+#    #+#              #
#    Updated: 2021/01/13 11:59:33 by clorin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = Cub3D

#	Sources

SRC			=	srcs/main.c srcs/images.c srcs/map.c srcs/player.c srcs/window.c srcs/tools.c srcs/setup.c \
				srcs/parse.c srcs/graphics.c srcs/game.c srcs/check_map.c srcs/keyboard.c srcs/render.c \
				srcs/map_utils.c srcs/raycasting.c srcs/textures.c srcs/mini_map_bonus.c \
				srcs/point.c srcs/facing.c srcs/inters_vert.c srcs/inters_horz.c srcs/free_functions.c \
				srcs/check_sprites.c srcs/error.c srcs/sprites.c srcs/textures_utils.c srcs/sprites_utils.c \
				srcs/bmp.c

B_SRC		=	bonus/srcs/main.c bonus/srcs/images.c bonus/srcs/map.c bonus/srcs/player.c bonus/srcs/window.c bonus/srcs/tools.c bonus/srcs/setup.c \
				bonus/srcs/parse.c bonus/srcs/graphics.c bonus/srcs/game.c bonus/srcs/check_map.c bonus/srcs/keyboard.c bonus/srcs/render.c \
				bonus/srcs/map_utils.c bonus/srcs/raycasting.c bonus/srcs/textures.c bonus/srcs/mini_map_bonus.c \
				bonus/srcs/point.c bonus/srcs/facing.c bonus/srcs/inters_vert.c bonus/srcs/inters_horz.c bonus/srcs/free_functions.c \
				bonus/srcs/check_sprites.c bonus/srcs/error.c bonus/srcs/sprites.c bonus/srcs/textures_utils.c bonus/srcs/sprites_utils.c \
				bonus/srcs/bmp.c

CC			=	clang

FLAGS		= -Werror -Wextra -Wall   -O3 -Ofast

HEADER		= -I includes/

B_HEADER	= -I bonus/includes/

OBJ 		= $(SRC:.c=.o)

B_OBJ		= $(B_SRC:.c=.o)

all : $(NAME)

.c.o:
			@${CC} ${FLAGS} ${HEADER} -c $< -o ${<:.c=.o}
			@echo "compilation : "$< "\033[32mok\033[0m"

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME) -L libft/ -lft -L./minilibx -lmlx -lXext -lX11 -lm
	@echo "création de Cub3D : \033[32mok\033[0m"

clean:
	rm -rf $(OBJ)
	rm -rf save.bmp

fclean: clean
	@make fclean -C libft/
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean all

bonus: fclean $(B_OBJ)
		@make -C libft/
		@echo "\n\033[0;32mCompiling bonus..."
		$(CC) -o $(NAME) $(FLAGS) $(B_HEADER) $(B_OBJ) -L libft/ -lft -L./minilibx -lmlx -lXext -lX11 -lm
		@echo "\033[0m"
test:	
	./$(NAME) maps/map.cub
bmp:
	./$(NAME) maps/map.cub --save

.PHONY: all clean fclean re bonus test bmp
