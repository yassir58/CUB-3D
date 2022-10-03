
SRCS= ./src/parse/convert_list.c ./src/parse/error.c ./src/parse/gnl.c\
./src/parse/list.c ./src/parse/list_helper.c\
./src/parse/parse.c ./src/parse/parse_helper.c ./src/parse/utils.c ./src/parse/validation.c\
./src/raycaster/angle_utils.c ./src/raycaster/raycaster.c ./src/raycaster/raycaster_utils.c ./src/raycaster/wall_collision.c\
./src/utils/draw_utils.c ./src/utils/init.c ./src/utils/utils.c ./src/utils/textures.c ./src/utils/init_2.c\
./src/window/events.c ./src/window/img_utils.c ./src/window/movement.c ./src/window/movement_bonus.c ./src/window/movement_utils.c ./src/window/window_utils.c
BONUS_SRC = $(SRCS) ./src/main_bonus.c
BONUS=cub3d_bonus
MANDATORY= $(SRCS) ./src/main.c
OBJS= $(MANDATORY:.c=.o)
BONUS_OBJS=$(BONUS_SRC:.c=.o)
FLAGS= -Wall -Wextra -Werror
LIB= -lmlx -framework OpenGL -framework AppKit
# LIB= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
HEADER= includes/cub3d.h
MYLIB=src/lib/libft/libft.a
NAME=cub3d
CC=gcc

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

# @$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
$(NAME):$(OBJS)
	@cd src/lib/libft && make && cd ../../..
	$(CC) $(FLAGS) $(OBJS) $(MYLIB) $(LIB) -o $(NAME)
bonus:$(BONUS_OBJS)
	@cd src/lib/libft && make && cd ../../..
	$(CC) $(FLAGS) $(BONUS_OBJS) $(MYLIB) $(LIB) -o $(BONUS)

all:$(NAME)

clean:
	@cd src/lib/libft && make clean && cd ../../..
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	@cd src/lib/libft && make fclean && cd ../../..
	rm -rf $(NAME) $(BONUS)
	
re:fclean all