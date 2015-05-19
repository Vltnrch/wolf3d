# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 10:49:38 by vroche            #+#    #+#              #
#    Updated: 2015/05/19 12:14:58 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

LIB = -framework OpenGL -framework AppKit \
		-L./minilibx_macos -lmlx -L./libft -lft

HDR = -I./minilibx_macos -I./libft

FLAGS = -Wall -Werror -Wextra

C = ft_drawline.c \
	ft_key.c \
	ft_manage.c \
	ft_minimap.c \
	ft_raycast.c \
	ft_teleport.c \
	ft_wolf.c \
	main.c \
	map.c \
	nbr_split.c

O = $(C:.c=.o)

all: $(NAME)

$(NAME): $(O)
	make -C ./libft
	make -C ./minilibx_macos
	gcc $(FLAGS) $(HDR) $(LIB) $(O) -o $(NAME)

%.o:%.c
	gcc $(FLAGS) $(HDR) -c $<

clean:
	make -C ./libft clean
	make -C ./minilibx_macos clean
	rm -f $(O)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib