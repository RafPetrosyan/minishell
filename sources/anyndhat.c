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

void	anyndhat(t_minishell *minishell)
{
	while (1)
	{
		minishell->str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		if (minishell->str == 0)
			return ;
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
}
