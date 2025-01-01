#include "minishell.h"

#include "minishell.h"

int cmds(t_tokens **tokens, t_minishell *minishell, int token_index)
{
	int fd = -1;
	int i = 0;
	int	saved_fd[2];

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	while (tokens[i] != NULL && tokens[i]->type != 1)
	{
		if (tokens[i]->type == 3)
		{
			if (fd != -1)
				close(fd);
			fd = open(tokens[i + 1]->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("Error creating file");
				return 1;
			}

			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("Error duplicating file descriptor");
				close(fd);
				return 1;
			}
			i += 2;
			// token_index += 2;
			continue;
		}
		if (tokens[i]->type == 5)
		{
			if (fd != -1)
				close(fd);
			fd = open(tokens[i + 1]->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("Error creating file");
				return 1;
			}

			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("Error duplicating file descriptor");
				close(fd);
				return 1;
			}
			i += 2;
			// token_index += 2;
			continue;
		}
		if (tokens[i]->type == 2)
		{
			if (fd != -1)
				close(fd);
			fd = open(tokens[i + 1]->str, O_APPEND);
			if (fd == -1)
			{
				perror("File chka");
				return 1;
			}

			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("Error duplicating file descriptor");
				close(fd);
				return 1;
			}
			i += 2;
			// token_index += 2;
			continue;
		}
		++i;
		// ++token_index;
	}

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
	
	if (builtins(&tokens[0], minishell, 0) == 2)
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
