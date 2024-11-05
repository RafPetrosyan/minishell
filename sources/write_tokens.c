#include "minishell.h"

void    write_dollar()
{
    printf("$");
}

void	write_non_quote(char *str, int *i, t_tokens *token, int *j)
{
    while (str[*i] != '\0')
    {  
        if (str[*i] == ' ' || str[*i] == '\0' || str[*i] == '\'' || str[*i] == '"')
            return ;
        if (str[*i] == '$')
            write_dollar();
        else
            token->str[*j] = str[*i];
        ++(*i);
        ++(*j);

    }
}

void write_one_quote(char *str, int *i, t_tokens *token, int *j)
{
    int flag;

    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '\'')
        {
            ++flag;
            ++(*i);
            continue;
        }
        if (flag == 2)
            return ;
        token->str[*j] = str[*i];
        ++(*i);
        ++(*j);
    }
}


void write_two_quote(char *str, int *i, t_tokens *token, int *j)
{
    int flag;

    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '"')
        {
            ++(*i);
            ++flag;
            continue;
        }
        if (flag == 2)
            return ;
        if (str[*i] == '$')
            write_dollar();
        else
            token->str[*j] = str[*i];
        ++(*i);
        ++(*j);
    }
}


