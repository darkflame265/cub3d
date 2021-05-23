# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 23:05:04 by kihkim            #+#    #+#              #
#    Updated: 2021/05/23 23:20:55 by kihkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#MLX = -lmlx -lm -framework OpenGL -framework AppKit
#MLX = -I /usr/include -g -L /usr/lib -lX11 -lmlx -lXext -lm -fsanitize=address
MLX = -lmlx -lX11 -lXext -lm -lbsd

NAME = cub3D

SRCS			=	cub3d.c \
					srcs/key_press.c \
					srcs/key_press2.c \
					srcs/draw.c\
					srcs/draw_bitmap.c\
					srcs/draw_bitmap_util.c\
					srcs/raycasting.c\
					srcs/raycasting2.c\
					srcs/raycasting3.c\
					srcs/raycasting_util.c\
					srcs/init_variable.c\
					srcs/init_map.c\
					srcs/init_map2.c\
					srcs/get_next_line_utils.c\
					srcs/get_next_line.c\
					srcs/get_next_line2.c\
					srcs/utils.c\
					srcs/parsing1.c\
					srcs/parsing2.c\
					srcs/pars_ceil_floor.c\
					srcs/check_file.c\
					srcs/check_map.c\
					srcs/parsing_util.c\
					srcs/parsing_util2.c\
					srcs/pars_def.c\
					srcs/memory_clean.c\
					srcs/set_image.c\

SRCS_BONUS = 	#srcs/key_press.c \

OBJSRCS = $(SRCS:.c=.o)

$(NAME) : $(OBJSRCS)
	@echo "\033[33m[Remove last version...]"
	@rm -rf Cub3D
	@echo "\033[33m[Libft compilation...]"
	@echo "\033[33m[Cub3D compilation...]"
	@gcc $(OBJSRCS) -I./includes -I./usr/include -Wall -Wextra -Werror $(MLX) -o $(NAME)
	@echo "\033[33m[Done !]"

all : $(NAME)

clean :
	rm -rf $(OBJSRCS)

fclean : clean
	rm -rf $(NAME)
	rm -rf bitmapImage.bmp

re : fclean all

bonus : $(NAME)
