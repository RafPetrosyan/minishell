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
	DIR *dir;

	if (str[0] == '.' || str[0] == '/')
	{
		dir = opendir(str);
		if (dir != 0)
		{
			g_exit_status = 126;
			write(2, " is a directory\n", 16);
			closedir(dir);
			exit (126);
		}
	}
}

int	ft_execve(t_minishell *minishell)
{
	int	status;
	int	id;
	char	**paths;

	paths = ft_split(find_to_env_export("PATH", minishell->env_list, &id), ':');
	if (paths == 0)
	{
		ft_printf("bash: %s:", minishell->cmd_arr[0]);
		write(2, " No such file or directory\n", 27);
		g_exit_status = 127;
		return (127);
	}

	id = fork();
	if (id > 0)
	{
		waitpid(-1, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	else if (id == 0)
	{
		execve(minishell->cmd_arr[0], minishell->cmd_arr, minishell->env_char);
		if (find_to_env_export("PATH", minishell->env_list, &id) != 0)
		{
			int	i;
			i = 0;
			while (paths[i] != 0)
			{
				paths[i] = ft_strjoin_free1(paths[i], minishell->cmd_arr[0], '/');
				if (access(paths[i], 0) == 0 && access(paths[i], 1) == 0)
					execve(paths[i], minishell->cmd_arr, minishell->env_char);
				++i;
			}
		}
		else
		{
			ft_printf("mini: %s:", minishell->cmd_arr[0]);
			write(2, " No such file or directory\n", 27);
			exit(126);
		}
		check_dir(minishell->cmd_arr[0]);
		if (access(minishell->cmd_arr[0], 0) == 0 && access(minishell->cmd_arr[0], X_OK) != 0 && minishell->cmd_arr[0][0] == '.')
		{
			ft_printf("mini: %s:", minishell->cmd_arr[0]);
			write(2, " Permission denied\n", 19);
			exit(126);
		}
		ft_printf("%s:", minishell->cmd_arr[0]);
		write(2, " command not found\n", 19);
		exit(127);
	}
	free_string_arr(paths, 0);
	return (0);
	// zut 0 em return arel
}
