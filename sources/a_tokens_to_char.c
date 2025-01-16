/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_tokens_to_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:30 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:31 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_arr(char **arr, t_minishell *minishell)
{
	int		i;

	i = 0;
	if (arr == 0)
		return ;
	while (arr[i] != 0)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	arr = 0;
	if (minishell != 0)
		minishell->env_char = 0;
}
