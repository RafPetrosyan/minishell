#include "minishell.h"

int pipe_commands_init(t_minishell *minishell, t_tokens **tokens)
{
	int token_index = 0;
	pid_t pid;
	int	status;
	int	her_doc_index;
	int	i;

	int backup_stdin  = dup(STDIN_FILENO);
	int backup_stdout = dup(STDOUT_FILENO);

	i = 0;
	her_doc_index = -1;
	while (i < minishell->pipe_count)
	{
		if (pipe(minishell->fd_arr[i]) == -1)
		{
			write(2, "pipe\n", 6);
			for (int j = 0; j < i; j++)
			{
				close(minishell->fd_arr[j][0]);
				close(minishell->fd_arr[j][1]);
			}
			return (1);
		}
		++i;
	}
	i = 0;
	while (i < minishell->pipe_count + 1)
	{
		pid = fork();
		if (pid < 0)
		{
			write(2, "fork\n", 5);
			return (1);
		}
		else if (pid == 0)
		{
			if (i > 0)
				dup2(minishell->fd_arr[i - 1][0], STDIN_FILENO);
			if (i < minishell->pipe_count)
				dup2(minishell->fd_arr[i][1], STDOUT_FILENO);
			for (int j = 0; j < minishell->pipe_count; j++)
			{
				close(minishell->fd_arr[j][0]);
				close(minishell->fd_arr[j][1]);
			}

			cmds(&tokens[token_index], minishell, her_doc_index);
			exit(g_exit_status);
		}
		else
		{
			if (i < minishell->pipe_count)
			{
				close(minishell->fd_arr[i][1]);
			}
			if (i > 0)
			{
				close(minishell->fd_arr[i - 1][0]);
			}
		}

		while (tokens[token_index] && tokens[token_index]->type != PIPE)
			token_index++;
		if (tokens[token_index] && tokens[token_index]->type == PIPE)
			token_index++;
		for (int j = 0; minishell->tokens[j]->type != PIPE; j++)
		{
			if (minishell->tokens[j]->type == HERE_DOCK)
				++her_doc_index;
		}
		
		++i;
	}

	i =0;
	while (i < minishell->pipe_count + 1)
	{
		waitpid(-1, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		++i;
	}

	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close(backup_stdin);
	close(backup_stdout);

	return (0);
}