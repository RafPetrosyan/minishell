/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:45 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/18 11:05:59 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_docs_init(t_minishell *minishell)
{
	int	i;
	int	doc_index;

	i = 0;
	doc_index = 0;
	while (minishell->tokens[i] != 0)
	{
		if (minishell->tokens[i]->type == HERE_DOCK)
		{
			if (pipe(minishell->doc_arr[doc_index]) == -1)
			{
				write(2, "Pipe_here_doc_Error!!!\n", 23);
				close_open_pipes(minishell->doc_arr, doc_index);
				free_memory(minishell, 0);
				return (1);
			}
			her_doc_run(minishell->tokens[i + 1]->str,
				minishell->doc_arr[doc_index][1], minishell);
			close(minishell->doc_arr[doc_index][1]);
			++doc_index;
		}
		++i;
	}
	return (0);
}
