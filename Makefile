NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_DIR		= minilibx-linux
LIBFT_DIR	= libft
SRCS		= src/main.c src/error.c src/file_utils.c src/map_parse.c \
			  src/path_check.c src/render.c src/hooks.c
OBJS		= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

