/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:42:58 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/18 13:32:22 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redir(int *i, int *fd, t_tokens **tokens, t_minishell *minishell)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(tokens[*i + 1]->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		ft_printf("mini: %s: No such file or directory\n", tokens[*i + 1]->str);
		dup2(minishell->saved_fd[0], STDIN_FILENO);
		dup2(minishell->saved_fd[1], STDOUT_FILENO);
		g_exit_status = 1;
		return (1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		ft_printf("Error duplicating file descriptor\n");
		close(*fd);
		return (1);
	}
	(*i) += 2;
	return (3);
}

int	out_append_redir(int *i, int *fd, t_tokens **tokens, t_minishell *minishell)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(tokens[*i + 1]->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		ft_printf("mini: %s: Permission denied\n", tokens[*i + 1]->str);
		dup2(minishell->saved_fd[0], STDIN_FILENO);
		dup2(minishell->saved_fd[1], STDOUT_FILENO);
		g_exit_status = 1;
		return (1);
	}
	if (dup2(*fd, STDOUT_FILENO) == -1)
	{
		ft_printf("Error duplicating file descriptor\n");
		close(*fd);
		return (1);
	}
	(*i) += 2;
	return (3);
}

int	in_redir(int *i, int *fd, t_tokens **tokens, t_minishell *minishell)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(tokens[*i + 1]->str, O_RDONLY);
	if (*fd == -1)
	{
		ft_printf("mini: %s: No such file or directory\n", tokens[*i + 1]);
		dup2(minishell->saved_fd[0], STDIN_FILENO);
		dup2(minishell->saved_fd[1], STDOUT_FILENO);
		g_exit_status = 1;
		return (1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		ft_printf("Error duplicating file descriptor\n");
		close(*fd);
		return (1);
	}
	(*i) += 2;
	return (3);
}

int	doc_red(int *i, int *fd, t_minishell *minishell, int *doc_index)
{
	if (*fd != -1)
		close(*fd);
	dup2(minishell->doc_arr[*doc_index + 1][0], STDIN_FILENO);
	*fd = minishell->doc_arr[*doc_index + 1][0];
	++(*doc_index);
	(*i) += 2;
	return (3);
}
