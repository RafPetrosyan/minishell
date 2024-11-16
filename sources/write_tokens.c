#include "minishell.h"

int	write_operator(char *str, int *i, t_minishell *minishell, t_tokens *token, int *j)
{
    int count;

    count = 0;
	if (str[*i] == '|' && ++count)
        token->str[(*j)++] = str[(*i)++];
    else if (str[(*i)] == '<' && str[(*i) + 1] != '<' && ++count)
        token->str[(*j)++] = str[(*i)++]; 
    else if (str[*i] == '>' && str[*i + 1] != '>'&& ++count)
        token->str[(*j)++] = str[(*i)++]; 
    else if (str[*i] == '<' && str[*i + 1] == '<')
	{
        count += 2;
        token->str[(*j)++] = str[(*i)++]; 
        token->str[(*j)++] = str[(*i)++]; 
	}
    else if (str[*i] == '>' && str[*i + 1] == '>')
	{
        count += 2;
        token->str[(*j)++] = str[(*i)++]; 
        token->str[(*j)++] = str[(*i)++]; 
	}
    return (count);
}

int	write_tokens(char *str, int *i, t_tokens **arr, int arr_i, t_minishell *minishell)
{
	int	j;
    int count;

	j = 0;
    count = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		++(*i);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
			count += write_one_quote(str, i, arr[arr_i], &j);
		else if (str[*i] == '"')
			count += write_two_quote(str, i, arr[arr_i], &j, minishell);
		else
        {
			count += write_non_quote(str, i, arr[arr_i], &j, minishell);
            if (str[*i - 1] == '|' || str[*i - 1] == '<' || str[*i - 1] == '>')
            {
                arr[arr_i]->str[j] = '\0';
                return (count);
            }
        }
		if (str[*i] == ' ' || str[*i] == '|' || str[*i] == '<' || str[*i] =='>')
			break ;
	}
	arr[arr_i]->str[j] = '\0';
    return (count);
}

void    set_type(char *str, int *i, t_tokens *token)
{
    if (str[*i] == '|')
        token->type = 1;
    else if (str[(*i)] == '<' && str[(*i) + 1] != '<')
        token->type = 2;
    else if (str[*i] == '>' && str[*i + 1] != '>')
        token->type = 3;
    else if (str[*i] == '<' && str[*i + 1] == '<')
        token->type = 4;
    else if (str[*i] == '>' && str[*i + 1] == '>')
        token->type = 5;
}

int	write_non_quote(char *str, int *i, t_tokens *token, int *j , t_minishell *minishell)
{
    int k;
    int count;

    k = *i;
    count = 0;
    while (str[*i] != '\0')
    {  
        if (str[*i] == '$')
            count += write_dollar(str, i, token, minishell, j);
        else if (check_operator(str, &k, minishell) != 0)
        {
            set_type(str, i, token);
            count += write_operator(str, i, minishell, token, j);
            return (count);
        }
        else
        {
            token->str[*j] = str[*i];
            ++count;
            ++(*i);
            ++(*j);
        }
        if (str[*i] == ' ' || str[*i] == '\'' || str[*i] == '"' || str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
        {
            token->type = 0;
            return (count);
        }
    }
    return (count);
}

int write_one_quote(char *str, int *i, t_tokens *token, int *j)
{
    int flag;
    int count;

    flag = 0;
    count = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '\'')
        {
            ++flag;
            ++(*i);
            continue;
        }
        if (flag == 2)
        {
            token->type = 0;
            return (count);
        }
        token->str[*j] = str[*i];
        ++count;
        ++(*i);
        ++(*j);
    }
    return (count);
}


int write_two_quote(char *str, int *i, t_tokens *token, int *j, t_minishell *minishell)
{
    int flag;
    int count;

    flag = 0;
    count = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '"')
        {
            ++(*i);
            ++flag;
            continue;
        }
        if (flag == 2)
        {
            token->type = 0;
            return (count);
        }
        if (str[*i] == '$')
            count += write_dollar_quote(str, i, token, minishell, j);
        else
        {
            token->str[*j] = str[*i];
            ++count;
            ++(*j);
            ++(*i);
        }
    }
    return (count);
}
