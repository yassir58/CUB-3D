
SRCS= src/test.c parse/test_parse.c src/lib/gnl/get_next_line.c src/window/img_utils.c src/test_utils.c \
src/window/window_utils.c src/init.c src/window/movement.c src/window/movement_utils.c src/math_utils.c
OBJS= $(SRCS:.c=.o)
FLAGS= -Wall -Wextra -Werror
LIB= -lmlx -framework OpenGL -framework AppKit
# LIB= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
HEADER= includes/cub3d.h
MYLIB=src/lib/libft/libft.a
NAME=cub3d
CC=gcc

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -Imlx -c $< -o $@
# @$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME):$(OBJS)
	@cd src/lib/libft && make && cd ../../..
	@$(CC) $(FLAGS) $(OBJS) $(MYLIB) $(LIB) -o $(NAME)

all:$(NAME)


clean: 
	cd src/lib/libft && make clean && cd ../../..
	rm $(OBJS)

fclean: clean 
	cd src/lib/libft && make fclean && cd ../../..
	rm $(NAME)
