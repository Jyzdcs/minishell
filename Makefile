NAME    := minishell

SRCDIR  := src
OBJDIR  := objs
SRCS    := $(shell find $(SRCDIR) -name '*.c')
OBJS    := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

LIBFT   := include/libft/libft.a

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I include/libft
LDFLAGS := -L include/libft -lft -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C include/libft

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) -C include/libft clean

fclean: clean
	$(RM) -f $(NAME)
	$(MAKE) -C include/libft fclean

re: fclean all

.PHONY: all clean fclean re