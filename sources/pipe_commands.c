#include "minishell.h"

int pipe_commands_init(t_minishell *minishell, t_tokens **tokens)
{
	int pipe_index = 0;
	int pid;
	int token_index = 0;

	while (pipe_index <= minishell->pipe_count)
	{
		if (pipe(minishell->fd_arr[pipe_index]) == -1)
		{
			perror("pipe");
			return (1);
		}
		if (pipe_index == 0)
		{
			minishell->fd_arr[minishell->pipe_count + 1][1] = dup(STDOUT_FILENO);
			minishell->fd_arr[minishell->pipe_count + 1][0] = dup(STDIN_FILENO);
		}

		if (pipe_index == 0)
			dup2(minishell->fd_arr[pipe_index][1], STDOUT_FILENO);
		else if (pipe_index < minishell->pipe_count)
		{
			dup2(minishell->fd_arr[pipe_index - 1][0], STDIN_FILENO);
			dup2(minishell->fd_arr[pipe_index][1], STDOUT_FILENO);
		}
		else
		{
			dup2(minishell->fd_arr[pipe_index - 1][0], STDIN_FILENO);
			dup2(minishell->fd_arr[minishell->pipe_count + 1][1], STDOUT_FILENO);
		}

		pid = fork();
		if (pid == 0)
		{
			for (int i = 0; i <= minishell->pipe_count; ++i)
			{
				close(minishell->fd_arr[i][0]);
				close(minishell->fd_arr[i][1]);
			}
			close(minishell->fd_arr[minishell->pipe_count + 1][0]);
			close(minishell->fd_arr[minishell->pipe_count + 1][1]);

			cmds(&tokens[token_index], minishell, token_index);
			// builtins(&tokens[token_index], minishell, token_index);
			exit(0);
		}
		else if (pid > 0) // Parent process
		{
			close(minishell->fd_arr[pipe_index][1]);
			if (pipe_index > 0)
				close(minishell->fd_arr[pipe_index - 1][0]);
		}
		else
		{
			perror("fork");
			return (1);
		}

		while (tokens[token_index] != 0 && tokens[token_index]->type != 1)
			++token_index;
		++token_index;
		++pipe_index;
	}

	dup2(minishell->fd_arr[minishell->pipe_count + 1][0], STDIN_FILENO);
	close(minishell->fd_arr[minishell->pipe_count + 1][0]);
	close(minishell->fd_arr[minishell->pipe_count + 1][1]);

	for (int i = 0; i <= minishell->pipe_count; ++i)
		waitpid(-1, NULL, 0);
	return (0);
}
