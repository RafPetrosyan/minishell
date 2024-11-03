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
        if (str[i] == '\'' && check_zuyg_slash(str, i) == 0)
        {
            if (check_one_quote(str, &i) == 0)
                return (0);
        }
        else if (str[i] == '"' && check_zuyg_slash(str, i) == 0)
        {
            if (check_two_quote(str, &i) == 0)
                return (0);
        }
        else
            ++i;
    }
    if (lenght != 0 && str[lenght - 1 ] == '\\' && !check_zuyg_slash(str, lenght - 1))
        return (printf("Error\n"));
    return (1);//ok
}

int	check_non_quote(char *str, int *i)
{
    int slash_flag;
    int count;

    count = 0;
    slash_flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '\\')
            ++slash_flag;
        if ((str[*i] == '\\' && slash_flag == 2) || (str[*i] != '\\' && slash_flag == 1) || (slash_flag == 0))
        {
            ++count;
            slash_flag = 0;
        }
        ++(*i);
        if ((str[*i] == ' ' && check_zuyg_slash(str, *i) == 0) || str[*i] == '\0')
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
    int slash_flag;
    int count;

    count = 0;
    flag = 0;
    slash_flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '"' && !(i != 0 && check_zuyg_slash(str, *i)))
            ++flag;
        if (str[*i] == '\\')
            ++slash_flag;
        if ((slash_flag == 2) || !(slash_flag == 1 && str[*i + 1] != '\0' && (str[*i + 1] == '"' || str[*i + 1] == '$' || str[*i + 1] == '\\')) || slash_flag == 0)
        {
            ++count;
            slash_flag = 0;
        }
        if (flag == 2)
            return (count - 2);//pakvel e
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

int check_zuyg_slash(char *str, int j)
{
    int count;

    count = 0;
    while (j > 0 && str[--j] == '\\')
        ++count;
    return (count % 2);
}