#include <minishell.h>

int	ft_cd(t_EnvList *env, char **tokens)
{
	if (tokens[1] == 0)
		return(cd_no_arguments(env));
	if (tokens[2] == 0)
	{
		if (tokens[1][0] == '~')
			return (cd_tilda(env, tokens[1]));
		if (tokens[1][0] == '-')
			return (cd_minus(env, tokens[1]));
		return (cd_non_symbol(env, tokens[1]));
	}
	g_exit_status = 1;
	printf("mini: cd:");
	write(2, " too many arguments\n", 20);
	return(1);
}
int	cd_non_symbol(t_EnvList *env, char *token)
{
	int		j;
	char	*pwd;

	j = 0;
	pwd = getcwd(0, 0);
	if (chdir(token) == 0)
	{
		if (find_to_env_export("OLDPWD", env, &j) != 0)
			free(find_to_env_export("OLDPWD", env, &j)->value);
		if (find_to_env_export("PWD", env, &j) != 0)
			free (find_to_env_export("PWD", env, &j)->value);
		ft_export_helper("OLDPWD", env);
		ft_export_helper("PWD", env);
		find_to_env_export("OLDPWD", env, &j)->value = pwd;
		find_to_env_export("PWD", env, &j)->value = getcwd(0, 0);
		if (find_to_env_export("PWD", env, &j)->value == 0)
		{
			ft_printf("mini: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			return (0);
		}
		return (0);
	}
	g_exit_status = 1;
	ft_printf("mini: cd: %s:", token);
	write(2, " No such file or directory\n", 27);
	return (1);
}

int	cd_tilda(t_EnvList *env, char *token)
{
	char	*path;
	char	*pwd;
	int		j;

	j = 0;
	path = malloc((ft_strlen(getenv("HOME")) + ft_strlen(token)) * sizeof(char));
	if (path == 0)
		return (printf("memory alocation error"));
	ft_strlcpy(path, getenv("HOME"), ft_strlen(getenv("HOME")) + 1, &j);
	ft_strlcpy(path, token + 1, ft_strlen(token), &j);
	path[j] = '\0';
	pwd = getcwd(0, 0);
	if (chdir(path) == 0)
	{
		if (find_to_env_export("OLDPWD", env, &j) != 0)
			free(find_to_env_export("OLDPWD", env, &j)->value);
		if (find_to_env_export("PWD", env, &j) != 0)
			free (find_to_env_export("PWD", env, &j)->value);
		ft_export_helper("OLDPWD", env);
		ft_export_helper("PWD", env);
		find_to_env_export("OLDPWD", env, &j)->value = pwd;
		find_to_env_export("PWD", env, &j)->value = getcwd(0, 0);
		free(path);
		return (0);
	}
	free(path);
	///////// error handle
	return (1);
}

int	cd_minus(t_EnvList *env, char *token)
{
	char		*path;
	int			j;
	t_EnvList	*oldpwd;
	char		*pwd;

	j = 0;
	oldpwd = find_to_env_export("OLDPWD", env, &j);
	if (oldpwd == 0 || oldpwd->value == 0)
		return (printf("mini: cd: OLDPWD not set\n"));
	path = malloc((ft_strlen(oldpwd->value) + ft_strlen(token)) * sizeof(char));
	if (path == 0)
		return (printf("memory alocation error"));
	j = 0;
	ft_strlcpy(path, oldpwd->value, ft_strlen(oldpwd->value) + 1, &j);
	ft_strlcpy(path, token + 1, ft_strlen(token), &j);
	path[j] = '\0';
	pwd = getcwd(0, 0);
	if (chdir(path) == 0)
	{
		if (find_to_env_export("OLDPWD", env, &j) != 0)
			free(find_to_env_export("OLDPWD", env, &j)->value);
		if (find_to_env_export("PWD", env, &j) != 0)
			free (find_to_env_export("PWD", env, &j)->value);
		ft_export_helper("OLDPWD", env);
		ft_export_helper("PWD", env);
		find_to_env_export("OLDPWD", env, &j)->value = pwd;
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
	char		*pwd;

	i = 0;
	node = find_to_env_export("HOME", env, &i);
	if (node == 0)
	{
		printf("mini: cd: HOME not set");
		return (1);
	}
	pwd = getcwd(0, 0);
	if (chdir(node->value) == 0)
	{
		if (find_to_env_export("OLDPWD", env, &i) != 0)
			free(find_to_env_export("OLDPWD", env, &i)->value);
		if (find_to_env_export("PWD", env, &i) != 0)
			free (find_to_env_export("PWD", env, &i)->value);
		ft_export_helper("OLDPWD", env);
		ft_export_helper("PWD", env);
		find_to_env_export("OLDPWD", env, &i)->value = pwd;
		find_to_env_export("PWD", env, &i)->value = getcwd(0, 0);
		return (0);
	}
	else
		printf("exit chem arel error cd-in\n");
	return (1);
}
