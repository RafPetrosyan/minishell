/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anyndhat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:32 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:33 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line_null(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ')
		{
			add_history(str);
			return ;
		}
		++i;
	}
}

void	show_ctl(int sig)
{
	struct termios	new;

	tcgetattr(0, &new);
	if (sig)
		new.c_lflag |= ECHOCTL;
	else
		new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}


void	anyndhat(t_minishell *minishell)
{
	while (minishell->str)
	{
		show_ctl(0);
		signal(SIGQUIT, SIG_IGN);
		handle_signal();
		minishell->str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		if (minishell->str == 0)
			break ;
		check_line_null(minishell->str);
		if (check_quote(minishell) == 1)
		{
			minishell->tokens = split_tokens(0, minishell->str, minishell, 0);
			if (check_syntax(minishell->tokens) == 2)
			{
				free_memory(minishell, 0);
				continue ;
			}
			allocated_fd_arrs(minishell);
			minishell->env_char = env_to_char(minishell->env_list);
			here_docs_init(minishell);
			if (minishell->pipe_count == 0 && cmds(minishell->tokens, minishell, -1) == 2)
				break ;
			else if (minishell->pipe_count != 0)
				pipe_commands_init(minishell, minishell->tokens);
		}
		else
			printf("Chakerty bacvel e u chi pakvel kam verjin simvoly '\\' e:\n");
		free_memory(minishell, 0);
	}
	printf("exit\n");
}
