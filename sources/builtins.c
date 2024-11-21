#include <minishell.h>

int check_n_flag(t_tokens **tokens, int *i)
{
	int j;
	int flag;

	flag = 1;
	while (tokens[*i] != 0  && tokens[*i]->type == 0)
	{
		j = 0;
		if (tokens[*i]->str[j] == '-')
		{
			++j;
			while (tokens[*i]->str[j] == 'n')
				++j;
			if (tokens[*i]->str[j] == '\0')
			{
				++(*i);
				flag = 0;
			}
			else
				return (flag);
		}
		else
			return (flag);
	}
	return (flag);
}

int builtins(t_tokens **tokens, t_minishell *minishell)
{
	if (tokens == 0 || tokens[0] == 0)
		return (0);
	if (ft_strcmp(tokens[0]->str, "echo") == 0)
		return (ft_echo(tokens, 1, 1, 0));
	else if (ft_strcmp(tokens[0]->str, "env") == 0)
		return (ft_env(minishell));
	else if (ft_strcmp(tokens[0]->str, "export") == 0)
		ft_export(minishell->env_list, tokens, &minishell->env_list);
	else if (ft_strcmp(tokens[0]->str, "unset") == 0)
		ft_unset(&(minishell->env_list), tokens);
	else if (ft_strcmp(tokens[0]->str, "print") == 0)
		print_env_keys(minishell->env_list);
	else if (ft_strcmp(tokens[0]->str, "pwd") == 0)
		ft_pwd(minishell->env_list);
	else if (ft_strcmp(tokens[0]->str, "cd") == 0)
		ft_cd(minishell->env_list, tokens);
	else
		printf("%s: command not found\n", tokens[0]->str);
	return (1);
}

int ft_echo(t_tokens **tokens, int flag, int i, int j)
{
	if (tokens[i] == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	flag = check_n_flag(tokens, &i);
	while (tokens[i] != 0 && tokens[i]->type == 0)
	{
		j = 0;
		while (tokens[i]->str[j] != '\0')
		{
			write(1, &tokens[i]->str[j], 1);
			++j;
		}
		if (tokens[i + 1] == 0)
			break ;
		if (tokens[i + 1]->type == 0)
			write(1, " ", 1);
		++i;
	}
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}

int ft_env(t_minishell *minishell)
{
	t_EnvList *temp;

	temp = minishell->env_list;
	while (temp != 0)
	{
		if (temp->value != 0)
		{
			printf("%s=", temp->key);
			printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_export(t_EnvList *env, t_tokens **tokens, t_EnvList **env_adress)
{
	int	i;
	int	j;
	t_EnvList	*export_node;

	i = 1;
	if (tokens[1] == 0)
	{
		print_export(env);
		return (0);
	}
	if (env == 0)
	{
		*env_adress = add_list(tokens[i]->str);
		++i;
	}
	while (tokens[i] != 0)
	{
		j = 0;
		export_node = find_to_env_export(tokens[i]->str, env, &j);
		if (export_node != 0)
		{
			if (tokens[i]->str[j] == '=')
			{
				if (export_node->value != 0)
					free(export_node->value);
				export_node->value =  ft_strdup(&(tokens[i]->str[j + 1]));
			}
		}
		else
		{
			while (env->next != 0)
				env = env->next;
			env->next = add_list(tokens[i]->str);
		}
		++i;
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
			free(unset_node);
			*env = next;
			return ;
		}
		temp = *env;
		while (temp->next != unset_node)
			temp = temp->next;
		free(unset_node);
		temp->next = next;
	}
}

int	ft_cd(t_EnvList *env, t_tokens **tokens)
{
	int			j;
	t_EnvList	*node;

	j = 0;
	if (tokens[1] == 0)
		return(cd_no_arguments(env));
	if (tokens[2] == 0)
	{
		if (tokens[1]->str[0] == '~')
			return (cd_tilda(env, tokens[1]));
		if (tokens[1]->str[0] == '-')
			return (cd_minus(env, tokens[1]));
		return (cd_non_symbol(env, tokens[1]));
	}
	printf("bash: cd: too many arguments\n");
	return(1);

}
int	cd_non_symbol(t_EnvList *env, t_tokens *token)
{
	int		j;

	j = 0;
	if (chdir(token->str) == 0)
	{
		free(find_to_env_export("OLDPWD", env, &j)->value);
		find_to_env_export("OLDPWD", env, &j)->value = find_to_env_export("PWD", env, &j)->value;
		find_to_env_export("PWD", env, &j)->value = getcwd(0, 0);
		return (0);
	}
	///////// error handle
	return (1);
}

int	cd_tilda(t_EnvList *env, t_tokens *token)
{
	char	*path;
	int		j;

	j = 0;
	path = malloc((ft_strlen(getenv("HOME")) + ft_strlen(token->str)) * sizeof(char));
	if (path == 0)
		return (printf("memory alocation error"));
	ft_strlcpy(path, getenv("HOME"), ft_strlen(getenv("HOME")) + 1, &j);
	ft_strlcpy(path, token->str + 1, ft_strlen(token->str), &j);
	path[j] = '\0';
	if (chdir(path) == 0)
	{
		free(find_to_env_export("OLDPWD", env, &j)->value);
		find_to_env_export("OLDPWD", env, &j)->value = find_to_env_export("PWD", env, &j)->value;
		find_to_env_export("PWD", env, &j)->value = getcwd(0, 0);
		free(path);
		return (0);
	}
	free(path);
	///////// error handle
	return (1);
}

int	cd_minus(t_EnvList *env, t_tokens *token)
{
	char		*path;
	int			j;
	t_EnvList	*oldpwd;

	j = 0;
	oldpwd = find_to_env_export("OLDPWD", env, &j);
	if (oldpwd->value == 0)
		return (printf("bash: cd: OLDPWD not set\n"));
	path = malloc((ft_strlen(oldpwd->value) + ft_strlen(token->str)) * sizeof(char));
	if (path == 0)
		return (printf("memory alocation error"));
	j = 0;
	ft_strlcpy(path, oldpwd->value, ft_strlen(oldpwd->value) + 1, &j);
	ft_strlcpy(path, token->str + 1, ft_strlen(token->str), &j);
	path[j] = '\0';
	if (chdir(path) == 0)
	{
		free(find_to_env_export("OLDPWD", env, &j)->value);
		find_to_env_export("OLDPWD", env, &j)->value = find_to_env_export("PWD", env, &j)->value;
		find_to_env_export("PWD", env, &j)->value = getcwd(0, 0);
		free(path);
		return (0);
	}
	free(path);
	///////// error handle
	return (1);
}

int	cd_no_arguments(t_EnvList *env)
{
	t_EnvList	*node;
	int			i;

	i = 0;
	node = find_to_env_export("HOME", env, &i);
	if (node == 0)
	{
		printf("bash: cd: HOME not set");
		return (1);
	}
	if (chdir(node->value) == 0)
	{
		free(find_to_env_export("OLDPWD", env, &i)->value);
		find_to_env_export("OLDPWD", env, &i)->value = find_to_env_export("PWD", env, &i)->value;
		find_to_env_export("PWD", env, &i)->value = getcwd(0, 0);
		return (0);
	}
	else
		printf("exit chem arel error cd-in\n");
	return (1);
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
