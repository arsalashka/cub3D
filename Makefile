# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maearly <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/01 15:15:49 by maearly           #+#    #+#              #
#    Updated: 2021/05/01 15:44:22 by maearly          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX = ./mlx

LFLAGS =	-L $(MLX) -lmlx -framework OpenGL -framework AppKit \

OTPFLAGS = -02

CFLAGS = -Wall -Wextra -Werror -O0 -g


LIST =			main.c parser/check_config.c \
                						parser/map_reader.c parser/find_plr.c parser/set_map.c \
                						parser/check_map.c parser/check_map2.c \
                						utils/ft_bzero.c utils/ft_calloc.c utils/ft_strcmp.c \
                						utils/list_manager.c utils/create_rgb.c \
                						utils/ft_strchr.c utils/ft_strdup.c \
                						utils/ft_strjoin.c utils/ft_strlen.c utils/get_next_line.c \
                						utils/ft_strncmp.c utils/ft_split.c \
                						utils/ft_atoi.c utils/ft_substr.c\
                						drawer/drawer.c drawer/position.c drawer/raycasting.c \
                						drawer/raycasting2.c drawer/position2.c \
                						drawer/sprite.c drawer/sprite2.c screenshot.c

OBJ = $(patsubst %.c,%.o,$(LIST))

D_FILES = $(patsubst %.c,%.d,$(LIST))


all:	$(NAME)

$(NAME) :	$(OBJ)
		make -C $(MLX) all
		gcc $(CFLAGS)  $(LFLAGS) $(OPTFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	gcc $(FLAGS) $(OPTFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean :
	rm -f $(OBJ) $(D_FILES)
	make -C $(MLX) clean

fclean : clean
	rm -f $(NAME) $(D_FILES)
	rm -f screenshot.bmp
	make -C $(MLX) clean

re : fclean all

.PHONY : all clean fclean re