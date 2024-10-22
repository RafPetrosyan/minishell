#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <readline/history.h>
# include <readline/readline.h>

int check_quote(char *str);
int check_one_quote(char *str, int *i);
int check_two_quote(char *str, int *i);
int	ft_strlen(const char *str);
int check_zuyg_slash(char *str, int j);


#endif