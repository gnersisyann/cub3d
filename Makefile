NAME = cub3D

CC = cc

RM = rm -f

MAKEFILE = Makefile

RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

define RUN_WITH_SPINNER
	@printf "$(BOLD)$(CYAN)%s$(RESET)\n" "$(1)"; \
	{ \
		set -e; \
		( $(2) ) & pid=$$!; \
		frames='| / - \\'; \
		while kill -0 $$pid 2>/dev/null; do \
			for frame in $$frames; do \
				if ! kill -0 $$pid 2>/dev/null; then \
					break; \
				fi; \
				printf "\r$(YELLOW)%s [%s]$(RESET)" "$(1)" "$$frame"; \
				sleep 0.1; \
			done; \
		done; \
		wait $$pid; status=$$?; \
		if [ $$status -ne 0 ]; then \
			printf "\r$(RED)%s [x]$(RESET)\n" "$(1)"; \
			exit $$status; \
		fi; \
		printf "\r$(GREEN)%s [OK]$(RESET)\n" "$(1)"; \
	}
endef

SRC_DIR = src/
INC_DIR = inc/
INC_FLAGS = -Iinc/ -Iinc/modules/

LIBFT_DIR = lib/libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = lib/minilibx-linux/
MLX = $(MLX_DIR)libmlx.a

CFLAGS = -Wall -Wextra -Werror $(INC_FLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR) #-g3

LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lm -lmlx -lXext -lX11

HEADERS = $(INC_DIR)cub3d.h \
          $(INC_DIR)defines.h \
          $(INC_DIR)modules/graphics.h \
          $(INC_DIR)modules/events.h \
          $(INC_DIR)modules/error.h \
          $(INC_DIR)modules/mlx_cub.h \
          $(INC_DIR)modules/utils.h \
          $(INC_DIR)modules/validation.h

SRC = $(SRC_DIR)main.c \
 \
      $(SRC_DIR)modules/error/error.c \
 \
      $(SRC_DIR)modules/graphics/init.c \
      $(SRC_DIR)modules/graphics/render.c \
      $(SRC_DIR)modules/graphics/modules/player/player_init.c \
      $(SRC_DIR)modules/graphics/modules/player/movement.c \
      $(SRC_DIR)modules/graphics/modules/player/rotation.c \
      $(SRC_DIR)modules/graphics/modules/render/raycast.c \
      $(SRC_DIR)modules/graphics/modules/render/ray_init.c \
      $(SRC_DIR)modules/graphics/modules/render/dda.c \
      $(SRC_DIR)modules/graphics/modules/render/render.c \
      $(SRC_DIR)modules/graphics/modules/render/render_door.c \
      $(SRC_DIR)modules/graphics/modules/render/render_door_layer.c \
      $(SRC_DIR)modules/graphics/modules/render/render_texture.c \
      $(SRC_DIR)modules/graphics/modules/render/sprite_render.c \
      $(SRC_DIR)modules/graphics/modules/render/sprite_render_utils.c \
      $(SRC_DIR)modules/graphics/modules/utils/utils.c \
      $(SRC_DIR)modules/graphics/modules/textures/get.c \
      $(SRC_DIR)modules/graphics/modules/textures/load.c \
      $(SRC_DIR)modules/graphics/modules/textures/utils.c \
      $(SRC_DIR)modules/graphics/modules/minimap/minimap.c \
      $(SRC_DIR)modules/graphics/modules/minimap/miniutils.c \
      $(SRC_DIR)modules/graphics/modules/minimap/light.c \
      $(SRC_DIR)modules/graphics/modules/minimap/helper.c \
      $(SRC_DIR)modules/graphics/modules/door/door.c \
      $(SRC_DIR)modules/graphics/modules/door/utils.c \
 \
      $(SRC_DIR)modules/events/keyboard.c \
      $(SRC_DIR)modules/events/mouse.c \
      $(SRC_DIR)modules/events/window.c \
 \
      $(SRC_DIR)modules/validation/validation.c \
      $(SRC_DIR)modules/validation/argument/argument.c \
      $(SRC_DIR)modules/validation/argument/modules/check_argc/check_argc.c \
      $(SRC_DIR)modules/validation/argument/modules/check_file_exists/check_file_exists.c \
      $(SRC_DIR)modules/validation/argument/modules/check_file_extension/check_file_extension.c \
      $(SRC_DIR)modules/validation/map/map.c \
      $(SRC_DIR)modules/validation/map/modules/parser/parser.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/content_splitter.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/line_validators.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/content_extractors.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/map_finder.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/map_continuity.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/duplicate_checker.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/required_checker.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/content_splitter/utils.c \
      $(SRC_DIR)modules/validation/map/modules/parser/modules/file_parser/file_parser.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/check_map.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/map_utils.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/map_validators.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/sprite_parser.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/flood_fill.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/flood_fill_utils.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/utils.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/door_validator.c \
      $(SRC_DIR)modules/validation/map/modules/check_map/door_validator_utils.c \
      $(SRC_DIR)modules/utils/cleanup.c \
      $(SRC_DIR)modules/utils/cleanup_utils.c \
      $(SRC_DIR)modules/utils/cleanup_mlx.c \
      $(SRC_DIR)modules/utils/cleanup_textures.c \
      $(SRC_DIR)modules/utils/init.c \
      $(SRC_DIR)modules/utils/init_utils.c \
      $(SRC_DIR)modules/validation/map/modules/check_config/check_config.c \
      $(SRC_DIR)modules/validation/map/modules/check_config/config_validators.c \
      $(SRC_DIR)modules/validation/map/modules/check_config/config_parsers.c \
      $(SRC_DIR)modules/validation/map/modules/check_config/animated_texture_parser.c \
      $(SRC_DIR)modules/validation/map/modules/check_config/config_utils.c \
      $(SRC_DIR)modules/validation/map/modules/check_config/utils.c \
      $(SRC_DIR)modules/mlx/mlx.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ) $(HEADERS) $(MAKEFILE)
	$(call RUN_WITH_SPINNER,Linking $(NAME),$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(call RUN_WITH_SPINNER,Compiling $(notdir $@),$(CC) $(CFLAGS) -c $< -o $@)

$(LIBFT):
	$(call RUN_WITH_SPINNER,Building libft,$(MAKE) -C $(LIBFT_DIR))

$(MLX):
	$(call RUN_WITH_SPINNER,Building minilibx,$(MAKE) -C $(MLX_DIR))

clean:
	$(call RUN_WITH_SPINNER,Cleaning libft,$(MAKE) -C $(LIBFT_DIR) clean)
	$(call RUN_WITH_SPINNER,Cleaning minilibx,$(MAKE) -C $(MLX_DIR) clean)
	$(call RUN_WITH_SPINNER,Removing objects,rm -rf $(OBJ_DIR))

fclean: clean
	$(call RUN_WITH_SPINNER,Purging libft,$(MAKE) -C $(LIBFT_DIR) fclean)
	$(call RUN_WITH_SPINNER,Purging minilibx,$(MAKE) -C $(MLX_DIR) clean)
	$(call RUN_WITH_SPINNER,Removing $(NAME),$(RM) $(NAME))

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
