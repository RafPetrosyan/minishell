#include "minishell.h"

#include "minishell.h"

int cmds(t_tokens **tokens, t_minishell *minishell, int doc_index)
{
	int fd = -1;
	int i = 0;
	int	saved_fd[2];

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	while (tokens[i] != NULL && tokens[i]->type != 1)
	{
		if (tokens[i]->type == OUT_REDIR)
		{
			if (fd != -1)
				close(fd);
			fd = open(tokens[i + 1]->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				write(2," No such file or directory\n", 27);
				dup2(saved_fd[0], STDIN_FILENO);
				dup2(saved_fd[1], STDOUT_FILENO);
				g_exit_status = 1;
				return 1;
			}

			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				write(2,"Error duplicating file descriptor\n", 34);
				close(fd);
				return 1;
			}
			i += 2;
			continue;
		}
		if (tokens[i]->type == OUT_APPEND_REDIR)
		{
			if (fd != -1)
				close(fd);
			fd = open(tokens[i + 1]->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				write(2," Permission denied\n", 19);
				dup2(saved_fd[0], STDIN_FILENO);
				dup2(saved_fd[1], STDOUT_FILENO);
				g_exit_status = 1;
				return 1;
			}

			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				write(2,"Error duplicating file descriptor\n", 34);
				close(fd);
				return 1;
			}
			i += 2;
			continue;
		}
		if (tokens[i]->type == IN_REDIR)
		{
			if (fd != -1)
				close(fd);
			fd = open(tokens[i + 1]->str, O_RDONLY);
			if (fd == -1)
			{
				write(2," No such file or directory\n", 27);
				dup2(saved_fd[0], STDIN_FILENO);
				dup2(saved_fd[1], STDOUT_FILENO);
				g_exit_status = 1;
				return 1;
			}

			if (dup2(fd, STDIN_FILENO) == -1)
			{
				write(2,"Error duplicating file descriptor\n", 34);
				close(fd);
				return 1;
			}
			i += 2;
			continue;
		}
		if (tokens[i]->type == HERE_DOCK)
		{
			if (fd != -1)
				close(fd);
			dup2(minishell->doc_arr[doc_index + 1][0], STDIN_FILENO);
			fd = minishell->doc_arr[doc_index + 1][0];
			++doc_index;
			i += 2;
			continue;
		}
		++i;
	}
	if (fd != -1)
		close(fd);

	int count = 0;
	int k=0;
	while (tokens[k] != 0 && tokens[k]->type != 1)
	{
		if (tokens[k]->type == 0)
			++count;
		else
			++k;
		++k;
	}
	
	if (minishell->cmd_arr != 0)
	{
		free(minishell->cmd_arr);
		minishell->cmd_arr = 0;
	}

	minishell->cmd_arr = malloc(sizeof(char *) * (count + 1));
	if (minishell->cmd_arr == 0)
	{
		printf("memmory error");
		return(2);
	}
	count = 0;
	k=0;
	while (tokens[k] != 0 && tokens[k]->type != 1)
	{
		if (tokens[k]->type == 0)
		{
			minishell->cmd_arr[count] = tokens[k]->str;
			++count;
		}
		else
			++k;
		++k;
	}
	minishell->cmd_arr[count] = 0;
	
	if (builtins(minishell) == 2)
	{
		if (fd != -1)
			close(fd);
		dup2(saved_fd[1], STDOUT_FILENO);
		return 2;
	}

	if (fd != -1)
		close(fd);
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	return 0;
}
