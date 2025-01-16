/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:05 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:06 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi(char *nptr, int *error)
{
	int					i;
	int					sign;
	unsigned long long	numb;

	i = 0;
	sign = 1;
	numb = 0;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= (-1);
		++i;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		numb = numb * 10 + nptr[i++] - '0';
	if (nptr[i] != '\0' || ((sign < 0 && (i > 20
					|| numb > (-1) * (unsigned long long)LONG_MIN))
			|| ((sign > 0 && (i > 19 || numb > LONG_MAX)))))
	{
		++(*error);
		ft_printf(" numeric argument required\n");
		return (255);
	}
	return (sign * numb);
}

int	ft_exit(t_minishell *minishell)
{
	int	error;

	error = 0;
	printf("exit\n");
	if (minishell->cmd_arr[1] == 0)
		return (2);
	g_exit_status = ft_atoi(minishell->cmd_arr[1], &error) % 256;
	if (minishell->cmd_arr[2] != 0 && error == 0)
	{
		g_exit_status = 1;
		ft_printf(" too many arguments\n");
		return (1);
	}
	if (minishell->cmd_arr[1] != 0)
	{
		free_memory(minishell, 1);
		exit(g_exit_status);
	}
	return (0);
}
