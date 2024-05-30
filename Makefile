CC=cc
CFLAGS=  -g #-fsanitize=address -DEBUG=1
GLFW = $(shell brew --prefix glfw)/lib

HEAP_CONTROL = 	heap_control/heap_control.c\
				heap_control/utils.c

EXECUTION = execution/main.c\
			execution/minimap.c\
			execution/utils.c\
			execution/init.c\
			execution/hooks.c\
			execution/update_vars.c\
			execution/cast_rays.c\
			execution/rendering.c

SRCS = 	$(HEAP_CONTROL)\
		$(EXECUTION)

INCLUDES = includes/cub3d.h includes/MLX42.h
LIBS = mlx/libmlx42.a -lglfw -L$(GLFW) -pthread -lm

OBJS = $(SRCS:.c=.o)

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ 

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -I./includes -o $@

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
