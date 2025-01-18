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

int	cmds(t_tokens **tokens, t_minishell *minishell, int doc_index)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	minishell->saved_fd[0] = dup(STDIN_FILENO);
	minishell->saved_fd[1] = dup(STDOUT_FILENO);
	while (tokens[i] != NULL && tokens[i]->type != 1)
	{
		if (tokens[i]->type == OUT_REDIR)
			if (out_redir(&i, &fd, tokens, minishell) == 3)
				continue ;
			else
				return (1);
		if (tokens[i]->type == OUT_APPEND_REDIR)
			if (out_append_redir(&i, &fd, tokens, minishell) == 3)
				continue ;
			else
				return (1);
		if (tokens[i]->type == IN_REDIR)
			if (in_redir(&i, &fd, tokens, minishell) == 3)
				continue ;
			else
				return (1);
		if (tokens[i]->type == HERE_DOCK)
			if (here_doc_redir(&i, &fd, minishell, &doc_index) == 3)
				continue ;
			else
				return (1);
		++i;
	}
	if (fd != -1)
		close(fd);
	int	count = 0;
	int	k=0;
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
		dup2(minishell->saved_fd[1], STDOUT_FILENO);
		return 2;
	}

	if (fd != -1)
		close(fd);
	dup2(minishell->saved_fd[0], STDIN_FILENO);
	dup2(minishell->saved_fd[1], STDOUT_FILENO);
	return 0;
}
