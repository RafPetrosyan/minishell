/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:52 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 21:50:56 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_commands_init(t_minishell *minishell, t_tokens **tokens)
{
	int	token_index;
	int	status;
	int	her_doc_index;
	int	i;
	int	saved_fd[2];

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	her_doc_index = -1;
	token_index = 0;
	if (open_pipes(minishell) != 0)
		return (1);
	open_and_run_forks(minishell, tokens, &token_index, &her_doc_index);
	i = 0;
	while (i < minishell->pipe_count + 1)
	{
		waitpid(-1, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		++i;
	}
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	close(saved_fd[0]);
	close(saved_fd[1]);
	return (0);
}
