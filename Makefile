CC= cc
CFLAGS=-Wall -Wextra -Werror
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

PARSING = parsing/pars.c\
		  parsing/get_next_line.c\
		  parsing/pars_utils.c

ft_functions = ft_functions/ft_atoi.c  ft_functions/ft_isalpha.c ft_functions/ft_strncmp.c ft_functions/ft_substr.c \
			   ft_functions/ft_split.c ft_functions/ft_strjoin.c ft_functions/ft_isalnum.c ft_functions/ft_strdup.c \
			   ft_functions/ft_strlen.c ft_functions/ft_memcpy.c ft_functions/ft_memmove.c ft_functions/ft_memset.c \
			   ft_functions/ft_strchr.c ft_functions/ft_strtrim.c ft_functions/ft_strnstr.c


SRCS = 	$(HEAP_CONTROL) $(EXECUTION) $(PARSING) $(ft_functions)

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
