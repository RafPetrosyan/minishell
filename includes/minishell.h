#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_token
{
    char    *str;
    int     token;
    // 1- word
    // 2- pipe
}   t_tokens;

typedef struct s_EnvList
{
    char    *key;
    char    *value;
    struct s_EnvList *next;
}   t_EnvList;


int check_quote(char *str);
int	check_non_quote(char *str, int *i);
int check_one_quote(char *str, int *i);
int check_two_quote(char *str, int *i);
int	ft_strlen(const char *str);
int check_zuyg_slash(char *str, int j);

//          ft_split
int	ft_get_word_len(char *str, int *i);
int	*malloc_word_len_arr(char *str);
int	ft_get_word_count(char *str);//, char c)

#endif