#include "../includes/minishell.h"

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] == str2[i])
            ++i;
        else
            return (str1[i] - str2[i]);
    }
    return (str1[i] - str2[i]);
}

void    print_export(t_EnvList  *env_list)
{
    t_EnvList   *temp;
    t_EnvList   *min;
    t_EnvList   *verjiny;

    verjiny = 0;
    while (1)
    {
        temp = env_list;
        min = 0;
        while (temp != 0)
        {
            if ((!verjiny || ft_strcmp(verjiny->key, temp->key) < 0) &&
                (!min || ft_strcmp(temp->key, min->key) < 0))
                min = temp;
            temp = temp->next;
        }
        if (min == 0)
            break;
        printf("declare -x %s=\"%s\"\n", min->key, min->value);
        verjiny = min;
    }
}