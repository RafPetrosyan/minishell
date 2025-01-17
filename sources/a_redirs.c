/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:38:25 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 23:38:26 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < minishell->pipe_count)
	{
		if (pipe(minishell->fd_arr[i]) == -1)
		{
			ft_printf("pipe\n");
			while (j < i)
			{
				close(minishell->fd_arr[j][0]);
				close(minishell->fd_arr[j][1]);
				++j;
			}
			return (1);
		}
		++i;
	}
	return (0);
}

void	prepare_for_the_next_command(int *i, int *token_index,
	t_minishell *minishell, int *her_doc_index)
{
	t_tokens	**tokens;
	int			j;

	j = 0;
	tokens = minishell->tokens;
	while (tokens[*token_index] && tokens[*token_index]->type != PIPE)
		(*token_index)++;
	if (tokens[*token_index] && tokens[*token_index]->type == PIPE)
		(*token_index)++;
	while (minishell->tokens[j]->type != PIPE)
	{
		if (minishell->tokens[j]->type == HERE_DOCK)
			++(*her_doc_index);
		++j;
	}
	++(*i);
}
