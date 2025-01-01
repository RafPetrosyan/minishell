#include "minishell.h"

int	ft_execve(t_minishell *minishell, t_tokens **tokens, int token_index)
{
	int	status;
	int	id;
	char	**paths;

	paths = ft_split(find_to_env_export("PATH", minishell->env_list, &id), ':');
	if (paths == 0)
	{
		printf("bash: %s: No such file or directory\n", minishell->cmd_arr[0]);
		exit(127);
	}
	id = fork();
	if (id > 0)
		waitpid(-1, &status, 0);
	else if (id == 0)
	{
		execve(minishell->cmd_arr[0], minishell->cmd_arr, minishell->env_char);
		if (find_to_env_export("PATH", minishell->env_list, &id) != 0)
		{
			int	i;
			i = 0;
			while (paths[i] != 0)
			{
				paths[i] = ft_strjoin_free1(paths[i], minishell->cmd_arr[0]);
				if (access(paths[i], 0) == 0 && access(paths[i], 1) == 0)
					execve(paths[i], minishell->cmd_arr, minishell->env_char);
				++i;
			}
		}
		else
		{
			printf("bash: %s: No such file or directory\n", minishell->cmd_arr[0]);
			exit(127);
		}
		printf("%s: command not found\n", minishell->cmd_arr[0]);
		exit(127);
	}
	free_string_arr(paths);
}
