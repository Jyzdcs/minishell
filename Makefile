NAME = minishell

SRCS = $(addprefix src/, \
						main.c \
						parser/parsing.c \
						expander/expanding.c \
						lexer/lexer.c \
						utils/tools.c \
						utils/trees.c )

OBJS = $(SRCS:src/%.c=objs/%.o)

LIBFT = include/libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cc -o $@ $^ -L include/libft -lft -lreadline -lhistory
	@echo COMPILED

objs/%.o: src/%.c
	@mkdir -p $(dir $@)
	@cc $(FLAGS) -I include/libft -c $< -o $@

$(LIBFT):
	@$(MAKE) -C include/libft

clean:
	@rm -rf objs
	@$(MAKE) -C include/libft clean
	@echo CLEANED

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C include/libft fclean

re: fclean all

.PHONY: all clean fclean re