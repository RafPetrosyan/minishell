# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:50:59 by rafpetro          #+#    #+#              #
#    Updated: 2025/01/16 16:51:00 by rafpetro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

READLINE = readline
CC = cc

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = 	includes/minishell.h \

SRCS_DIR = sources/

OBJS_DIR = objects/

SRCS_NAME =	a_minishell.c \
			a_ft_split_tokens.c \
			a_quotes.c \
			write_tokens.c\
			dollar.c\
			a_libft.c\
			a_builtins.c\
			a_env.c\
			a_export_sort.c\
			a_ft_cd.c\
			a_ft_export.c\
			a_ft_echo.c\
			a_tokens_to_char.c\
			ft_execve.c\
			a_ft_split.c\
			a_env_to_char.c\
			a_ft_itoa.c\
			a_pipe_commands.c\
			in_redir.c\
			a_ft_exit.c\
			a_ft_printf.c\
			here_doc.c\
			here_doc_init.c\
			a_memmory_free.c\
			anyndhat.c\
			a_allocated_fd_arrs.c\
			a_redirs.c\
			open_and_run_forks.c

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tokenization
	@mkdir -p $(OBJS_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

re: fclean all

.PHONY: all clean fclean re