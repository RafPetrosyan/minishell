#include <minishell.h>

int	builtins(t_minishell *minishell)
{
	if (minishell->cmd_arr == 0 || minishell->cmd_arr[0] == 0)
		return (0);
	if (ft_strcmp(minishell->cmd_arr[0], "echo") == 0)
		return (ft_echo(minishell->cmd_arr, 1, 1, 0));
	else if (ft_strcmp(minishell->cmd_arr[0], "env") == 0)
		return (ft_env(minishell));
	else if (ft_strcmp(minishell->cmd_arr[0], "export") == 0)
		return (ft_export(minishell->env_list, minishell->cmd_arr, 1, 0));
	else if (ft_strcmp(minishell->cmd_arr[0], "unset") == 0)
		return (ft_unset(&(minishell->env_list), minishell->cmd_arr));
	else if (ft_strcmp(minishell->cmd_arr[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(minishell->cmd_arr[0], "cd") == 0)
		return (ft_cd(minishell->env_list, minishell->cmd_arr));
	else if (ft_strcmp(minishell->cmd_arr[0], "exit") == 0)
		return (ft_exit(minishell));
	return (ft_execve(minishell));
}

int	ft_env(t_minishell *minishell)
{
	t_EnvList	*temp;

	temp = minishell->env_list;
	while (temp != 0)
	{
		if (temp->value != 0 && temp->type == 0)
		{
			printf("%s=", temp->key);
			printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
	g_exit_status = 0;
	return (0);
}

int	ft_unset(t_EnvList **env, char **tokens)
{
	int			i;
	int			j;
	t_EnvList	*unset_node;

	i = 1;
	while (tokens[i] != 0 && *env != 0)
	{
		j = 0;
		unset_node = find_to_env_export(tokens[i], *env, &j);
		if (unset_node != 0 && ft_strcmp(unset_node->key, "_") == 0)
		{
			++i;
			continue ;
		}
		ft_unset_helper(unset_node, env);
		++i;
	}
	g_exit_status = 0;
	return (0);
}

void	ft_unset_helper(t_EnvList *unset_node, t_EnvList **env)
{
	t_EnvList	*next;
	t_EnvList	*temp;

	if (unset_node != 0)
	{
		next = unset_node->next;
		if (*env == unset_node)
		{
			free(unset_node->key);
			free(unset_node->value);
			free(unset_node);
			*env = next;
			return ;
		}
		temp = *env;
		while (temp->next != unset_node)
			temp = temp->next;
		free(unset_node->key);
		free(unset_node->value);
		free(unset_node);
		temp->next = next;
	}
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(0, 0);
	if (path != 0)
	{
		printf("%s\n", path);
		free(path);
	}
	else
	{
		ft_printf("mini: cd: ");
		write(2, "Goyutyun chunecogh panakum enq\n", 32);
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}
