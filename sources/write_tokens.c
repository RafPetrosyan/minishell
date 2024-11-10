#include "minishell.h"

void	write_tokens(char *str, int *i, t_tokens **arr, int arr_i, t_minishell *minishell)
{
	int	j;

	j = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		++(*i);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
			write_one_quote(str, i, arr[arr_i], &j);
		else if (str[*i] == '"')
			write_two_quote(str, i, arr[arr_i], &j, minishell);
		else
			write_non_quote(str, i, arr[arr_i], &j, minishell);
		if (str[*i] == ' ')
			break ;
	}
	arr[arr_i]->str[j] = '\0';
}

void	write_non_quote(char *str, int *i, t_tokens *token, int *j , t_minishell *minishell)
{
    while (str[*i] != '\0')
    {  
        if (str[*i] == ' ' || str[*i] == '\0' || str[*i] == '\'' || str[*i] == '"')
            return ;
        if (str[*i] == '$')
            write_dollar(str, i, token, minishell, j);
        else
        {
            token->str[*j] = str[*i];
            ++(*i);
            ++(*j);
        }

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


void write_two_quote(char *str, int *i, t_tokens *token, int *j, t_minishell *minishell)
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
            write_dollar(str, i, token, minishell, j);
        else
        {
            token->str[*j] = str[*i];
            ++(*j);
            ++(*i);
        }
    }
}


