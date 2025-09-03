NAME = cub3D

CC = cc

RM = rm -f

MAKEFILE = Makefile

SRC_DIR = src/
INC_DIR = inc/
INC_FLAGS = -Iinc/ -Iinc/modules/

LIBFT_DIR = lib/libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = lib/minilibx-linux/
MLX = $(MLX_DIR)libmlx.a

CFLAGS = -g $(INC_FLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR) #-Wall -Wextra -Werror

LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lm -lmlx -lXext -lX11

SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)modules/error/error.c \
      $(SRC_DIR)modules/graphics/init.c \
      $(SRC_DIR)modules/graphics/render.c \
      $(SRC_DIR)modules/events/keyboard.c \
      $(SRC_DIR)modules/events/window.c \
	  $(SRC_DIR)modules/parsing/check.c \
	  $(SRC_DIR)modules/parsing/validate.c
	  

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ) $(INC_DIR) $(MAKEFILE)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(NAME)

re: fclean all

valgrind:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline.supp ./cub3D

.PHONY: all clean fclean re