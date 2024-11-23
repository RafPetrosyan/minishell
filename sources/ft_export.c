#include <minishell.h>

int	ft_export(t_EnvList *env, t_tokens **tokens, t_EnvList **env_adress)
{
	int	i;
	int	j;
	t_EnvList	*export_node;

	i = 1;
	j = 0;
	if (tokens[1] == 0)
	{
		print_export(env);
		return (0);
	}
	while (tokens[i] != 0)
	{
		ft_export_helper(tokens[i]->str, env);
		export_node = find_to_env_export(tokens[i]->str, env, &j);
		export_node->type = 0;
		++i;
	}
	return (0);
}

int	ft_export_helper(char *str, t_EnvList *env)
{
	t_EnvList	*export_node;
	int			j;

	j = 0;
	export_node = find_to_env_export(str, env, &j);
	if (export_node != 0)
	{
		if (str[j] == '=')
		{
			if (export_node->value != 0)
				free(export_node->value);
			export_node->value = ft_strdup(&(str[j + 1]));
		}
	}
	else
	{
		while (env->next != 0)
			env = env->next;
		env->next = add_list(str);
	}
	return (0);
}

t_EnvList *find_to_env_export(char *str, t_EnvList *env, int *i)
{
	int j;

	while (env != 0)
	{
		j = 0;
		while (env->key[j] == str[j])
		{
			if (env->key[j + 1] == '\0' && (str[j + 1] == '\0' || str[j + 1] == '=' ))
			{
				++j;
				*i += j;
				return (env);
			}
			++j;
		}
		env = env->next;
	}
	return (0);
}
