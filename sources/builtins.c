#include <minishell.h>

int builtins(t_tokens **tokens, t_minishell *minishell)
{
	if (tokens == 0 || tokens[0] == 0)
		return (0);
	if (ft_strcmp(tokens[0]->str, "echo") == 0)
		return (ft_echo(tokens, 1, 1, 0));
	else if (ft_strcmp(tokens[0]->str, "env") == 0)
		return (ft_env(minishell));
	else if (ft_strcmp(tokens[0]->str, "export") == 0)
		return (ft_export(minishell->env_list, tokens, &minishell->env_list));
	else if (ft_strcmp(tokens[0]->str, "unset") == 0)
		return(ft_unset(&(minishell->env_list), tokens));
	else if (ft_strcmp(tokens[0]->str, "print") == 0)
		print_env_keys(minishell->env_list);
	else if (ft_strcmp(tokens[0]->str, "pwd") == 0)
		return(ft_pwd(minishell->env_list));
	else if (ft_strcmp(tokens[0]->str, "cd") == 0)
		return(ft_cd(minishell->env_list, tokens));
	else if (ft_strcmp(tokens[0]->str, "exit") == 0)
		return (2);
	else
		return( 0 || printf("%s: command not found\n", tokens[0]->str));
	return (1);
}

int ft_env(t_minishell *minishell)
{
	t_EnvList *temp;

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
	return (0);
}

int	ft_unset(t_EnvList **env, t_tokens **tokens)
{
	int			i;
	int			j;
	t_EnvList	*unset_node;
	t_EnvList	*temp;

	i = 1;
	while (tokens[i] != 0 && *env != 0)
	{
		j = 0;
		unset_node = find_to_env_export(tokens[i]->str, *env, &j);
		if (ft_strcmp(unset_node->key, "_") == 0)
		{
			++i;
			continue ;
		}
		ft_unset_helper(unset_node, env);
		++i;
	}
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



int	ft_pwd()
{
	char	*path;

	path = getcwd(0, 0);
	if (path != 0)
	{
		printf("%s\n", path);
		free(path);
	}// 	else error
	return (0);
}

void print_env_keys(t_EnvList *temp)
{
	while (temp != 0)
	{
		if (temp->value != 0)
		{
			printf("%s ", temp->key);
		}
		temp = temp->next;
	}
}
