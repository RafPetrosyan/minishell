#include "minishell.h"

int get_key_len(char *str)
{
    int i;

    i = 0;
    while (str[i] != '=' && str[i] != ' ' && str[i] != '\0')
        ++i;
    return i;
}

int get_value_len(char *str, int i)
{
    ++i;
    while (str[i] != '\0' && str[i] != ' ')

}

t_EnvList   *add_list(char  *str)
{
    t_EnvList   *node;
    int i;
    int len;

    i = 0;
    len = get_key_len(str);
    node = malloc(sizeof(t_EnvList));
    node->key = malloc((len + 1) * sizeof(char));
    while (i < len)
        node->key[i] = str[i++];
    
}

t_EnvList *env_to_list(char **env)
{
    int i;

    i = 0;
    while (env[i] != 0)
    {
        add_list(env);
    }
    return (0);
}
