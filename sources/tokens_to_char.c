#include "minishell.h"

char	**tokens_to_char(t_tokens **arr)
{
	int		i;
	char	**split;

	i = 0;
	while (arr[i] != 0)
		++i;
	split = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (arr[i] != 0)
	{
		if (arr[i]->type == 1)
		{
			split[i++] = 0;
			continue;
		}
		split[i] = ft_strdup(arr[i]->str);
		++i;
	}
	split[i] = 0;
	return (split);
}

void	free_tokens_char(t_minishell *minishell)
{
	int	i;


	i = 0;
	if (minishell->tokens == 0)
		return ;
	while (minishell->tokens[i] != 0)
	{
		free(minishell->tokens[i]);
		++i;
		if (minishell->pipe_count2 != 0 && minishell->tokens[i] == 0)
		{
			--minishell->pipe_count2;
			++i;
		}
	}
	free(minishell->tokens);
}

void	free_string_arr(char **arr)
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
}

