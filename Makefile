# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 23:05:04 by kihkim            #+#    #+#              #
#    Updated: 2021/05/17 18:10:39 by kihkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#MLX = -lmlx -lm -framework OpenGL -framework AppKit
#MLX = -I /usr/include -g -L /usr/lib -lX11 -lmlx -lXext -lm -fsanitize=address
MLX = -lmlx -lX11 -lXext -lm -lbsd

NAME = cub3D

SRCS			=	main2.c \
					srcs/key_press.c \
					srcs/draw.c\
					srcs/raycasting.c\
					srcs/init_variable.c\
					srcs/get_next_line_utils.c\
					srcs/get_next_line.c\
					srcs/utils.c\
					srcs/parsing1.c\
					srcs/pars_ceil_floor.c\
					srcs/check_file.c\
					srcs/check_map.c\
					srcs/parsing_util.c\
					srcs/parsing_util2.c\
					srcs/pars_def.c\

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
	rm -rf cub3d.bmp

re : fclean all

bonus : $(NAME)
