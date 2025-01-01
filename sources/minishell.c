#include "../includes/minishell.h"
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_tokens **tokens;

	int status;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->env_list = env_to_list(env);
	minishell->str = "";
	while (minishell->str != 0)
	{
		minishell->str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		if (!minishell->str)
			return (0);
		if (minishell->str[0] != '\0')  // inchqan space ka ancnem ete datark eghav chavelacnem
			add_history(minishell->str);
		if (check_quote(minishell) == 1)
		{
			minishell->pipe_count = 0;
			minishell->cmd_arr = 0;
			tokens = split_tokens(0, minishell);
			minishell->fd_arr = malloc((minishell->pipe_count + 2) * sizeof(int *));
			for (int i = 0; i < minishell->pipe_count + 2; i++)
				minishell->fd_arr[i] = malloc(2 * sizeof(int));
			if (minishell->fd_arr == 0)
			{
				printf("Memmory error!!!!!");
				return(1);
			}
			minishell->pipe_count2 = minishell->pipe_count;
			// minishell->tokens = tokens_to_char(tokens);
			minishell->env_char = env_to_char(minishell->env_list);
			if (minishell->pipe_count == 0 && cmds(tokens, minishell, 0) == 2)
				break ;
			else if (minishell->pipe_count != 0)
			{
				pipe_commands_init(minishell, tokens);
			}
			delete_tokens(tokens);
			// free_tokens_char(minishell);
			free_string_arr(minishell->env_char);
		}
		else
			printf("Chakerty bacvel e u chi pakvel kam verjin simvoly '\\' e:\n");
		free(minishell->str);
		if (minishell->fd_arr != 0)
		{
			for (int i = 0; i < minishell->pipe_count + 2; i++)
				free(minishell->fd_arr[i]);
			free(minishell->fd_arr);
		}
	}
	if (minishell->fd_arr != 0)
	{
		for (int i = 0; i < minishell->pipe_count + 2; i++)
			free(minishell->fd_arr[i]);
		free(minishell->fd_arr);
	}
	delete_tokens(tokens);
	// free_tokens_char(minishell);
	free_string_arr(minishell->env_char);
	delete_env_list(minishell->env_list);
	free(minishell->str);
	free(minishell);
	return (0);
}

void	delete_tokens(t_tokens	**tokens)
{
	int	i;

	i = 0;
	if (tokens == 0)
		return;
	while (tokens[i] != 0)
	{
		free(tokens[i]->str);
		free(tokens[i]);
		tokens[i] = 0;
		++i;
	}
	free(tokens);
}

void print_tokens_info(char *str, t_minishell *minishell, t_tokens **tokens)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc_word_len_arr(str, minishell);
	while(arr[i] != -1)
		printf("token[%d] lenght = %d\n", i, arr[i++]);
	i = 0;
	printf("tokens: \n");
	while (tokens[i] != 0)
	{
		printf("%s=%d\n", tokens[i]->str, tokens[i]->type);
		++i;
	}
	printf("Pipe Count: %d \n", minishell->pipe_count);
	free(arr);
	printf("--------------------------------------------------\n");
}
