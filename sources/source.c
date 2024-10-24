#include "minishell.h"

int check_quote(char *str)
{
    int i;
    int lenght;

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
    return (1);//ok
}

int check_one_quote(char *str, int *i)
{
    int flag;

    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '\'')
            ++flag;
        // if (str[*i] == '\'' && flag == 1 && check_zuyg_slash(str, *i) == 1)
        //     --flag;
        ++(*i);
        if (flag == 2)
            return (1);//pakvel e
    }
    printf("Error \n");
    return (0);// chi pakvel 
}


int check_two_quote(char *str, int *i)
{
    int flag;

    flag = 0;
    while (str[*i] != '\0')
    {
        if (str[*i] == '"' && !(i != 0 && check_zuyg_slash(str, *i)))
            ++flag;
        ++(*i);
        if (flag == 2)
            return (1);//pakvel e
    }
    printf("Error 2 \n");
    return (0);// chi pakvel 
}
int	ft_strlen(const char *str)
{
	int	i;

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