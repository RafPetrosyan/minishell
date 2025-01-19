/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anyndhat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:32 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/18 00:11:29 by rafpetro         ###   ########.fr       */
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
// void print_tokens_info(char *str, t_minishell *minishell, t_tokens **tokens)
// {
// 	int	*arr;
// 	int	i;

// 	i = 0;
// 	arr = malloc_word_len_arr(str, minishell);
// 	while(arr[i] != -1)
// 		printf("token[%d] lenght = %d\n", i, arr[i++]);
// 	i = 0;
// 	printf("tokens: \n");
// 	while (tokens[i] != 0)
// 	{
// 		printf("%s=%d\n", tokens[i]->str, tokens[i]->type);
// 		++i;
// 	}
// 	printf("Pipe Count: %d \n", minishell->pipe_count);
// 	free(arr);
// 	printf("--------------------------------------------------\n");
// }

void	signals(void)
{
	show_ctl(0);
	signal(SIGQUIT, SIG_IGN);
	handle_signal();
}

void	anyndhat(t_minishell *mini)
{
	while (mini->str)
	{
		signals();
		mini->str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		if (mini->str == 0)
			break ;
		check_line_null(mini->str);
		if (check_quote(mini) == 1)
		{
			mini->tokens = split_tokens(0, mini->str, mini, 0);
			if (check_syntax(mini->tokens) == 2 && free_memory(mini, 0))
				continue ;
			allocated_fd_arrs(mini);
			mini->env_char = env_to_char(mini->env_list);
			if (here_docs_init(mini) == 1)
				continue ;
			if (mini->pipe_count == 0 && cmds(mini->tokens, mini, -1) == 2)
				break ;
			else if (mini->pipe_count != 0)
				pipe_commands_init(mini, mini->tokens);
		}
		free_memory(mini, 0);
	}
	printf("exit\n");
}
