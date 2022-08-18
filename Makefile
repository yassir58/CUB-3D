
SRCS= src/test.c parse/test_parse.c src/lib/gnl/get_next_line.c src/window/img_utils.c src/test_utils.c src/window/window_utils.c src/init.c src/window/movement.c src/window/movement_utils.c
OBJS= $(SRCS:.c=.o)
FLAGS= -Wall -Wextra -Werror
LIB= -Lmlx -lmlx -framework OpenGL -framework AppKit
HEADER= includes/cub3d.h
MYLIB=src/lib/libft/libft.a
NAME=cub3d
CC=gcc

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME):$(OBJS)
	@cd src/lib/libft && make && cd ../../..
	@$(CC) $(FLAGS) $(OBJS) $(MYLIB) $(LIB) -o $(NAME)

all:$(NAME)

libft_clean:
	@cd src/lib/libft && make clean && cd ../../..

clean: 
	@rm $(OBJS)

fclean: clean 
	@rm $(NAME) src/lib/libft/libft.a
