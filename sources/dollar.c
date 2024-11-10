#include "../includes/minishell.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size, int *j)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[(*j)++] = src[i];
		++i;
	}
	return (ft_strlen(src));
}

int find_to_env(char *str, int *i, t_EnvList *env)
{
    int j;

    while (env != 0)
    {
        j = 0;
        while (env->key[j] == str[*i + j])
        {
            if (env->key[j + 1] == '\0' && (str[*i + j + 1] == ' ' || str[*i + j + 1] == '\'' 
                || str[*i + j + 1] == '"' || str[*i + j + 1] == '\0' || str[*i + j + 1] == '\\' || str[*i + j + 1] == '$'))
            {
                *i += j + 1;
                return (ft_strlen(env->value));
            }
            ++j;
        }
        env = env->next;
    }
    while (str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"' && str[*i] != '\0' && str[*i] != '\\' && str[*i] != '$')
        ++(*i);
    return (0);
}

int	dollar_arg_len(char *str, int *index, t_minishell *minishell)
{
    ++(*index);
    if (str[*index] == '\0' || str[*index] == '\\' || str[*index] == ' ')
        return (1);
    if (str[*index] == '0' && ++(*index))
        return (4);
    if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
        return (0);
    if (str[*index] == '\'' || str[*index] == '"')
        return (0);
	return (find_to_env(str, index, minishell->env_list));
}

void    write_dollar(char *str, int *index, t_tokens *token, t_minishell *minishell, int *j)
{
    ++(*index);
    if (str[*index] == '\0' || (str[*index] == '\\' || str[*index] == ' '))
    {
        token->str[*j] = '$';
        ++(*j);
        return ;
    }
    ////// $$ = 22701
    if (str[*index] == '0' && ++(*index))
    {
        ft_strlcpy(token->str + *j, "bash", 5, j);
        return ;
    }
    if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
        return ;
    if (str[*index] == '\'' || str[*index] == '"')
        return;
	find_to_env_write(str, index, minishell->env_list, token, j);
}

void find_to_env_write(char *str, int *i, t_EnvList *env, t_tokens *token, int *k)
{
    int j;
    int flag;

    while (env != 0)
    {
        j = 0;
        while (env->key[j] == str[*i + j])
        {
            if (env->key[j + 1] == '\0' && (str[*i + j + 1] == ' '
                || str[*i + j + 1] == '\'' || str[*i + j + 1] == '"'
                || str[*i + j + 1] == '\0' || str[*i + j + 1] == '\\' || str[*i + j + 1] == '$'))
            {
                ft_strlcpy(token->str, env->value, ft_strlen(env->value) + 1, k);
                *i += j + 1;
                return ;
            }
            ++j;
        }
        env = env->next;
    }
    while (str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"' && str[*i] != '\0' && str[*i] != '\\' && str[*i] != '$')
        ++(*i);
    return ;
}
