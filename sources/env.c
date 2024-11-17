#include "minishell.h"

int	get_key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != ' ' && str[i] != '\0')
		++i;
	return (i);
}

int	get_value_len(char *str, int i)
{
	int	count;

	count = 0;
	++i;
	while (str[i] != '\0')
	{
		++count;
		++i;
	}
	return (count);
}

t_EnvList	*add_list(char *str)
{
	t_EnvList	*node;
	int			i;
	int			j;
	int			len;

	i = 0;
	j = 0;
	len = get_key_len(str);
	node = malloc(sizeof(t_EnvList));
	node->next = 0;
	node->key = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		node->key[i] = str[i];
		++i;
	}
	node->key[i] = '\0';
	len = get_value_len(str, i);
	if (str[i] == '=')
		node->value = malloc((len + 1) * sizeof(char));
	else
	{
		node->value = 0;
		return (node);
	}
	++i;
	while (j < len)
		node->value[j++] = str[i++];
	node->value[j] = '\0';
	return (node);
}

t_EnvList	*env_to_list(char **env)
{
	t_EnvList	*first;
	t_EnvList	*temp;
	int			i;

	i = 0;
	first = add_list(env[i++]);
	temp = first;
	while (env[i] != 0)
	{
		temp->next = add_list(env[i++]);
		temp = temp->next;
	}
	return (first);
}

int	delete_env_list(t_EnvList *list)
{
	t_EnvList	*temp;

	while (list != 0)
	{
		temp = list->next;
		free(list->key);
		if (list->value != 0)
			free(list->value);
		free(list);
		list = temp;
	}
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_EnvList *temp;
// 	t_EnvList *temp1;

// 	temp = env_to_list(env);
// 	temp1 = temp;
// 	while (temp != 0)
// 	{
// 	    printf("%s=", temp->key);
// 	    printf("%s\n", temp->value);
// 	    temp = temp->next;
// 	}
//     delete_env_list(temp1);
//     return 0;
// }