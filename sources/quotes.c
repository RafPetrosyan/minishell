#include "minishell.h"

int check_quote(char *str)
{
    int i;
    int lenght;

    if (!str)
        return (0);
    i = 0;
    lenght = ft_strlen(str);
    while (i < lenght)
    {
        if (str[i] == '\'')
        {
            if (check_one_quote(str, &i) == 0)
                return (0);
        }
        else if (str[i] == '"')
        {
            if (check_two_quote(str, &i) == 0)
                return (0);
        }
        else
            ++i;
    }
    if (lenght != 0 && str[lenght - 1 ] == '\\')
    {
        printf("Error\n");
        return (0);
    }
    return (1);//ok
}

int	check_non_quote(char *str, int *i)
{
    int count;

    count = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '$')
            count += dollar_arg_len(str, i);// --(*i)
        ++(*i);
        if (str[*i] == ' ' || str[*i] == '\0')
            return (count);
    }
    return (count);
}

int check_one_quote(char *str, int *i)
{
    int flag;
    int count;

    flag = 0;
    count = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '\'')
            ++flag;
        ++(*i);
        ++count;
        if (flag == 2)
            return (count - 2);//pakvel e
    }
    printf("Error \n");
    return (0);// chi pakvel 
}


int check_two_quote(char *str, int *i)
{
    int flag;
    int count;

    count = 0;
    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '"')
            ++flag;
        if (flag == 2)
            return (count - 2);//pakvel e
        if (str[*i] == '$')
            count += dollar_arg_len(str, *i);// --(*i)
        ++(*i);
    }
    printf("Error 2 \n");
    return (0);// chi pakvel 
}

int	ft_strlen(const char *str)
{
	int	i;

    if (!str)
        return (0);
	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}
