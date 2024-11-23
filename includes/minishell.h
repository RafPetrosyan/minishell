#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
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

typedef struct	s_EnvList
{
	char	*key;
	char	*value;
	struct	s_EnvList *next;
	int		type;// 0-print  1-nonprint
}	t_EnvList;

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
int	    write_tokens(char *str, int *i, t_tokens **arr, int arr_i, t_minishell *minishell);
int        write_non_quote(char *str, int *i, t_tokens *token, int *j , t_minishell *minishell);
int        write_one_quote(char *str, int *i, t_tokens *token, int *j);
int        write_two_quote(char *str, int *i, t_tokens *token, int *j, t_minishell *minishell);
t_tokens    **split_tokens(char *str, int i, t_minishell *minishell);


t_EnvList *env_to_list(char **env);
int delete_env_list(t_EnvList *list);

/////////       dollar       /////////

int		find_to_env(char *str, int *i, t_EnvList *env);
int		find_to_env_write(char *str, int *i, t_EnvList *env, t_tokens *token, int *k);
int		dollar_arg_len(char *str, int *index, t_minishell *minishell);
int		dollar_arg_len_quote(char *str, int *index, t_minishell *minishell);
int		write_dollar(char *str, int *index, t_tokens *token, t_minishell *minishell, int *j);
int		write_dollar_quote(char *str, int *index, t_tokens *token, t_minishell *minishell, int *j);

/////////		env			/////////

t_EnvList	*add_list(char *str);

/////////       libft       /////////

size_t	ft_strlcpy(char *dst, char *src, size_t size, int *j);
char	*ft_strdup(char *s);

////////        xary        ////////

int		check_operator(char *str, int *i, t_minishell *minishell);
void	print_env_keys(t_EnvList *temp);


int ft_strcmp(char *str1, char *str2);

int	ft_echo(t_tokens **tokens, int flag, int i, int j);
int	ft_env(t_minishell *minishell);
int	builtins(t_tokens **tokens, t_minishell *minishell);


///////         token tpel    ////////

void print_tokens_info(char *str, t_minishell *minishell, t_tokens **tokens);


//////          export          /////

void	print_export(t_EnvList *env_list);
int		ft_export(t_EnvList *env, t_tokens **tokens, t_EnvList **env_adress);
t_EnvList *find_to_env_export(char *str, t_EnvList *env, int *i);


//////			builtin			/////
int		ft_unset(t_EnvList **env, t_tokens **tokens);
void	ft_unset_helper(t_EnvList *unset_node, t_EnvList **env);
int		ft_pwd();
int		ft_cd(t_EnvList *env, t_tokens **tokens);
int		cd_tilda(t_EnvList *env, t_tokens *token);
int		cd_no_arguments(t_EnvList *env);
int		cd_minus(t_EnvList *env, t_tokens *token);
int	cd_non_symbol(t_EnvList *env, t_tokens *token);
int	ft_export_helper(char *str, t_EnvList *env);
void	delete_tokens(t_tokens	**tokens);


#endif