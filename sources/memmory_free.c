/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmory_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:50 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:51 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(t_minishell *minishell, int code)
{
	delete_tokens(minishell->tokens, minishell);
	free_string_arr(minishell->env_char, minishell);
	free(minishell->cmd_arr);
	minishell->cmd_arr = 0;
	delete_fd_arrs(minishell);
	minishell->pipe_count = 0;
	minishell->here_doc_count = 0;
	free(minishell->str);
	if (code == 1)
	{
		delete_env_list(minishell->env_list);
		free(minishell);
		exit(g_exit_status);
	}
}

void	delete_tokens(t_tokens	**tokens, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (tokens == 0)
		return;
	while (tokens[i] != 0)
	{
		free(tokens[i]->str);
		free(tokens[i]);
		tokens[i] = 0;
		++i;
	}
	free(tokens);
	minishell->tokens = 0;
}

void	delete_fd_arrs(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->pipe_count != 0 && minishell->fd_arr != 0)
	{
		while (i < minishell->pipe_count && minishell->fd_arr[i] != 0)
		{
			free(minishell->fd_arr[i]);
			minishell->fd_arr[i++] = 0;
		}
	}
	free(minishell->fd_arr);
	minishell->fd_arr = 0;

	i = 0;
	if (minishell->here_doc_count !=0 && minishell->doc_arr != 0)
	{
		while (i < minishell->here_doc_count && minishell->doc_arr[i] != 0)
		{
			free(minishell->doc_arr[i]);
			minishell->doc_arr[i++] = 0;
		}
	}
	free(minishell->doc_arr);
	minishell->doc_arr = 0;
}
