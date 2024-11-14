// #include "../includes/minishell.h"

// int check_operator(char *str, int *i, t_minishell *minishell)
// {
//     if (str[*i] == '|' && str[*i + 1] != '|' && ++(*i))
//         return (1);
//     else if (str[*i] == '<' && str[*i + 1] != '<' && ++(*i))
//         return (1);
//     else if (str[*i] == '>' && str[*i + 1] != '>' && ++(*i))
//         return (1);
//     else if (str[*i] == '<' && str[*i + 1] == '<' && ((*i) += 2))
//         return (2);
//     else if (str[*i] == '>' && str[*i + 1] == '>' && ((*i) += 2))
//         return (2);
//     return (0);
// }

// int	check_non_quote(char *str, int *i, t_minishell *minishell)
// {
//     int count;
//     int operator;

//     count = 0;
//     while (str[*i] != '\0')
//     {
//         if (str[*i] == '$')
//         {
//             count += dollar_arg_len(str, i, minishell);
//         }
//         else if (operator = check_operator(str, i, minishell))
//             return (operator);
//         else
//         {
//             ++count;
//             ++(*i);
//         }
//         if (str[*i] == ' ' || str[*i] == '\0' || str[*i] == '\'' || str[*i] == '"' || str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
//             return (count);
//     }
//     return (count);
// }

// int main(int argc, char **argv, char **env)
// {
//     int i=0;
//     char str[] = "hell0 h     elil";
//     t_minishell *shell = malloc(sizeof(t_minishell));
//     shell->env_list = env_to_list(env);

//     printf("%d\n", check_non_quote(str,&i, shell));
//     printf("%d\n", check_non_quote(str,&i, shell));
//     printf("%d\n", check_non_quote(str,&i, shell));
//     printf("%d\n", check_non_quote(str,&i, shell));
    

//     delete_env_list(shell->env_list);
//     free(shell);
//     return (0);
// }