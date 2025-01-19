/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:40 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:40 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dir(char *str)
{
	DIR	*dir;

	if (str[0] == '.' || str[0] == '/')
	{
		if ((str[0] == '.' && str[1] == 0)
			|| (str[0] == '.' && str[1] == '.' && str[2] == '\0'))
		{
			g_exit_status = 2;
			ft_printf("mini: %s: filename argument required\n", str);
			exit (2);
		}
		dir = opendir(str);
		if (dir != 0)
		{
			g_exit_status = 126;
			ft_printf("mini: %s: is a directory\n", str);
			closedir(dir);
			exit (126);
		}
	}
}

int	ft_execve(t_minishell *minishell)
{
	int		status;
	int		id;
	char	**paths;

	paths = ft_split(find_to_env_export("PATH", minishell->env_list, &id), ':');
	id = fork();
	if (id > 0)
	{
		waitpid(-1, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	else if (id == 0)
		ft_execve_helper3(minishell, paths, id);
	free_string_arr(paths, 0);
	return (0);
}

void	ft_execve_helper1(t_minishell *minishell, char **paths)
{
	check_dir(minishell->cmd_arr[0]);
	if (access(minishell->cmd_arr[0], 0) == 0)
	{
		if (access(minishell->cmd_arr[0], X_OK) != 0)
		{
			ft_printf("mini: %s: Permission denied\n", minishell->cmd_arr[0]);
			free_string_arr(paths, 0);
			exit(126);
		}
		if (minishell->cmd_arr[0][0] == '.' || minishell->cmd_arr[0][0] == '/')
			execve(minishell->cmd_arr[0],
				minishell->cmd_arr, minishell->env_char);
	}
}

void	ft_execve_helper2(t_minishell *minishell, char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != 0)
	{
		paths[i] = ft_strjoin_free1(paths[i], minishell->cmd_arr[0], '/');
		check_dir(minishell->cmd_arr[0]);
		if (access(paths[i], 0) == 0)
		{
			if (access(paths[i], 1) == 0)
				execve(paths[i], minishell->cmd_arr, minishell->env_char);
			ft_printf("mini: %s: Permission denied\n", minishell->cmd_arr[0]);
			free_string_arr(paths, 0);
			exit(126);
		}
		++i;
	}
}

void	ft_execve_helper3(t_minishell *minishell, char **paths, int id)
{
	if (minishell->cmd_arr[0][0] == '/' || minishell->cmd_arr[0][0] == '.')
		ft_execve_helper1(minishell, paths);
	if (paths == 0)
	{
		ft_printf("bash: %s:\
 No such file or directory\n", minishell->cmd_arr[0]);
		exit(127);
	}
	if (find_to_env_export("PATH", minishell->env_list, &id) != 0)
		ft_execve_helper2(minishell, paths);
	else
	{
		ft_printf("mini: %s:\
 No such file or directory\n", minishell->cmd_arr[0]);
		exit(126);
	}
	ft_printf("'%s': command not found\n", minishell->cmd_arr[0]);
	exit(127);
}
