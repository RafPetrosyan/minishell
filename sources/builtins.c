#include <minishell.h>

int ft_echo(t_tokens **tokens, int flag, int i, int j);

int check_n_flag(t_tokens **token, int *i)
{
    int j;
    int flag;

    flag = 1;
    while (token[*i] != 0 && token[*i]->type == 0)
    {
        j = 0;
        if (token[*i]->str[j] == '-')
        {
            ++j;
            while (token[*i]->str[j] == 'n')
                ++j;
            if (token[*i]->str[j] == '\0')
            {
                ++(*i);
                flag = 0;
            }
            else
                return (flag);
        }
        else
            return (flag);
    }
    return (flag);
}

int builtins(t_tokens **tokens, t_minishell *minishell)
{
    if (tokens == 0 || tokens[0] == 0)
        return (0);
    if (ft_strcmp(tokens[0]->str, "echo") == 0)
        return (ft_echo(tokens, 1, 1, 0));
    else if (ft_strcmp(tokens[0]->str, "env") == 0)
        return (ft_env(minishell));
    // else if (ft_strcmp(tokens->str, "export") == 0)
    //     ft_export();
    // else if (ft_strcmp(tokens->str, "pwd") == 0)
    //     ft_pwd();
    else
        printf("%s: command not found\n", tokens[0]->str);
    return (1);
}

int ft_echo(t_tokens **tokens, int flag, int i, int j)
{
    if (tokens[i] == 0)
    {
        write(1, "\n", 1);
        return (0);
    }
    flag = check_n_flag(tokens, &i);
    while (tokens[i] != 0 && tokens[i]->type == 0)
    {
        j = 0;
        while (tokens[i]->str[j] != '\0')
        {
            write(1, &tokens[i]->str[j], 1);
            ++j;
        }
        if (tokens[i + 1] == 0)
            break ;
        if (tokens[i + 1]->type == 0)
            write(1, " ", 1);
        ++i;
    }
    if (flag == 1)
        write(1, "\n", 1);
    return (0);
}

int ft_env(t_minishell *minishell)
{
    t_EnvList *temp;

    temp = minishell->env_list;
    while (temp != 0)
    {
        printf("%s=", temp->key);
        printf("%s\n", temp->value);
        temp = temp->next;
    }
    return (0);
}