#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_token
{
    char    *str;
    int     type;
    // 0 = word
    // 1 = pipe
    // 2 = <
    // 3 = >
    // 4 = <<
    // 5 = >>
}   t_tokens;

typedef struct s_EnvList
{
    char    *key;
    char    *value;
    struct s_EnvList *next;
}   t_EnvList;

typedef struct s_minishell
{
    t_EnvList   *env_list;
}   t_minishell;

int check_quote(char *str, t_minishell *minishell);
int	check_non_quote(char *str, int *i, t_minishell *minishell);
int check_one_quote(char *str, int *i);
int check_two_quote(char *str, int *i, t_minishell *minishell);
int	ft_strlen(char *str);

/////////       tokenization       /////////

int         ft_get_word_len(char *str, int *i, t_minishell *minishell);
int         *malloc_word_len_arr(char *str, t_minishell *minishell);
int         ft_get_word_count(char *str, t_minishell *minishell);
void	    write_tokens(char *str, int *i, t_tokens **arr, int arr_i, t_minishell *minishell);
void        write_non_quote(char *str, int *i, t_tokens *token, int *j , t_minishell *minishell);
void        write_one_quote(char *str, int *i, t_tokens *token, int *j);
void        write_two_quote(char *str, int *i, t_tokens *token, int *j, t_minishell *minishell);
t_tokens    **split_tokens(char *str, int i, t_minishell *minishell);


t_EnvList *env_to_list(char **env);
int delete_env_list(t_EnvList *list);

/////////       dollar       /////////

int     find_to_env(char *str, int *i, t_EnvList *env);
void    find_to_env_write(char *str, int *i, t_EnvList *env, t_tokens *token, int *k);
int     dollar_arg_len(char *str, int *index, t_minishell *minishell);
void    write_dollar(char *str, int *index, t_tokens *token, t_minishell *minishell, int *j);

/////////       libft       /////////



////////        xary        ////////

int check_operator(char *str, int *i, t_minishell *minishell);

#endif