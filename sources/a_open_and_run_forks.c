/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_run_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:49:02 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/17 16:31:10 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kapel_forkery_ashxatacnel(int i, t_minishell *minishell,
	t_tokens **tokens, int *her_doc_index)
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(minishell->fd_arr[i - 1][0], STDIN_FILENO);
	if (i < minishell->pipe_count)
		dup2(minishell->fd_arr[i][1], STDOUT_FILENO);
	while (j < minishell->pipe_count)
	{
		close(minishell->fd_arr[j][0]);
		close(minishell->fd_arr[j][1]);
		++j;
	}
	cmds(tokens, minishell, *her_doc_index);
	exit(g_exit_status);
}

int	open_and_run_forks(t_minishell *minishell,
	t_tokens **tokens, int *token_index, int *her_doc_index)
{
	int		i;
	int		pid;

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
			kapel_forkery_ashxatacnel(i, minishell,
				&tokens[*token_index], her_doc_index);
		else
		{
			if (i < minishell->pipe_count)
				close(minishell->fd_arr[i][1]);
			if (i > 0)
				close(minishell->fd_arr[i - 1][0]);
		}
		prepare_for_the_next_command(&i, token_index, minishell, her_doc_index);
	}
	return (0);
}
