/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:47 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/18 13:30:15 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	steghcel_cmd_arr(t_tokens **tokens, t_minishell *minishell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != 0 && tokens[i]->type != 1)
	{
		if (tokens[i]->type == 0)
			++count;
		else
			++i;
		++i;
	}
	minishell->cmd_arr = malloc(sizeof(char *) * (count + 1));
	if (minishell->cmd_arr == 0)
	{
		ft_printf("memmory error");
		free_memory(minishell, 1);
		exit(55);
	}

}

void	grel_cmd_arr(t_tokens **tokens, t_minishell *minishell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != 0 && tokens[i]->type != 1)
	{
		if (tokens[i]->type == 0)
		{
			minishell->cmd_arr[count] = tokens[i]->str;
			++count;
		}
		else
			++i;
		++i;
	}
	minishell->cmd_arr[count] = 0;
}
int helper(t_tokens **tokens, t_minishell *mini, int doc_index, int *fd)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL && tokens[i]->type != 1)
	{
		if (tokens[i]->type == OUT_REDIR)
			if (out_redir(&i, fd, tokens, mini) == 3)
				continue ;
			else
				return (1);
		if (tokens[i]->type == OUT_APPEND_REDIR)
			if (out_append_redir(&i, fd, tokens, mini) == 3)
				continue ;
			else
				return (1);
		if (tokens[i]->type == IN_REDIR)
			if (in_redir(&i, fd, tokens, mini) == 3)
				continue ;
			else
				return (1);
		if (tokens[i]->type == 4 && doc_red(&i, fd, mini, &doc_index) == 3)
				continue ;
		++i;
	}
	return (0);
}

int	cmds(t_tokens **tokens, t_minishell *minishell, int doc_index)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	minishell->saved_fd[0] = dup(STDIN_FILENO);
	minishell->saved_fd[1] = dup(STDOUT_FILENO);
	if (helper(tokens, minishell, doc_index, &fd) == 1)
		return (1);
	if (fd != -1)
		close(fd);
	steghcel_cmd_arr(tokens, minishell);
	grel_cmd_arr(tokens, minishell);
	if (builtins(minishell) == 2)
	{
		if (fd != -1)
			close(fd);
		dup2(minishell->saved_fd[1], STDOUT_FILENO);
		return 2;
	}
	if (fd != -1)
		close(fd);
	dup2(minishell->saved_fd[0], STDIN_FILENO);
	dup2(minishell->saved_fd[1], STDOUT_FILENO);
	return 0;
}

