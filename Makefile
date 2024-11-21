NAME = minishell

READLINE = readline
CC = cc

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wextra -Werror -g $(INC_DIRS) #-g3 -fsanitize=address
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

SRCS_DIR = sources/

OBJS_DIR = objects/

SRCS_NAME = minishell.c \
			ft_split.c \
			quotes.c \
			write_tokens.c\
			env.c\
			dollar.c\
			builtins.c\
			export_sort.c\
			libft.c
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(READLINE_LIB_PATH) -lncurses -l$(READLINE) -o $@

linux_minishell: $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(READLINE_LIB_PATH) -lncurses -l$(READLINE) -o $(NAME)

config_readline:
	./$(LIBS_DIR)/config_readline readline

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	@$(RM) $(NAME)
	make clean -C $(LIBS_DIR)/readline-8.2

fclean_linux: clean
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean fclean_linux re config_readline
