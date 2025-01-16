/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_allocated_fd_arrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:49:36 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:49:37 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocated_fd_arrs(t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->fd_arr = malloc((minishell->pipe_count) * sizeof(int *));
	if (minishell->pipe_count != 0 && minishell->fd_arr == 0)
	{
		printf("Memmory error!!!!!");
		free_memory(minishell, 0);
		exit(55);
	}
	while (i < minishell->pipe_count)
		minishell->fd_arr[i++] = malloc(2 * sizeof(int));
	i = 0;
	minishell->doc_arr = malloc((minishell->here_doc_count) * sizeof(int *));
	if (minishell->here_doc_count != 0 && minishell->doc_arr == 0)
	{
		printf("Memmory error!!!!!");
		free_memory(minishell, 0);
		exit(55);
	}
	while (i < minishell->here_doc_count)
		minishell->doc_arr[i++] = malloc(2 * sizeof(int));
}
