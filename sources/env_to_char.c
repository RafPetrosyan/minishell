#include "../includes/minishell.h"

char	**env_to_char(t_EnvList *env_list)
{
	int	i;
	char **env;
	t_EnvList	*temp;

	i = 0;
	temp = env_list;
	while (temp != 0)
	{
		// if (ft_strcmp(temp->key, "SHLVL") == 0)
		// 	ft_change_shlvl(temp);
		if (temp->value != 0)
			++i;
		temp = temp->next;
	}
	env = malloc((i + 1) * sizeof(char *));
	if (env == 0)
		return (0);
	env_to_char_helper(env, env_list);
	return (env);
}
void	env_to_char_helper(char **env, t_EnvList *env_list)
{
	int	i;
	t_EnvList	*temp;
	char	*str;
	char	arr[2];

	i = 0;
	temp = env_list;
	arr[0] = '=';
	arr[1] = '\0';
	while (temp != 0)
	{ 
		if (temp->value != 0)
		{
			str = ft_strjoin(temp->key, arr);
			env[i] = ft_strjoin(str, temp->value);
			free(str);
			++i;
		}
		temp =temp->next;
	}
	env[i] = 0;
}
void	ft_change_shlvl(t_EnvList *shlvl)
{
	char	*temp;

	temp = shlvl->value;
	shlvl->value = ft_itoa(ft_atoi(shlvl->value) + 1);
	free(temp);
}