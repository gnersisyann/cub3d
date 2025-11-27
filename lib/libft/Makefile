NAME = libft.a

HEADER = libft.h

CFLAGS = -Wall -Wextra -Werror

MAKEFILE = Makefile

RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
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

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_split.c ft_putnbr_fd.c ft_substr.c \
			ft_strtrim.c ft_strjoin.c ft_strmapi.c ft_strnstr.c ft_striteri.c ft_strcmp.c ft_strstr.c \
			ft_free_array.c ft_strndup.c ft_skip_whitespace.c ft_trim_whitespace.c get_next_line.c

BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(BONUS_OBJ) $(HEADER) $(MAKEFILE)
	$(call RUN_WITH_SPINNER,Archiving $(NAME),ar crs $(NAME) $(OBJ) $(BONUS_OBJ))

%.o: %.c
	$(call RUN_WITH_SPINNER,Compiling $(notdir $@),cc $(CFLAGS) -c $< -o $@)

bonus: $(BONUS_OBJ) $(HEADER)
	$(call RUN_WITH_SPINNER,Archiving bonus objects,ar crs $(NAME) $(BONUS_OBJ))

clean:
	$(call RUN_WITH_SPINNER,Cleaning libft objects,rm -f $(OBJ) $(BONUS_OBJ))

fclean: clean
	$(call RUN_WITH_SPINNER,Removing $(NAME),rm -f $(NAME))

re: fclean all

.PHONY: all clean fclean re
