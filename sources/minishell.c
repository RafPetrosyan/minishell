#include "../includes/minishell.h"
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_tokens **tokens;

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
			tokens = split_tokens(0, minishell);
			minishell->tokens = tokens_to_char(tokens);
			minishell->env_char = env_to_char(minishell->env_list);
			// print_tokens_info(str, minishell, tokens);
			if (builtins(tokens, minishell, env) == 2) // nor env sarqel
				break ;
			delete_tokens(tokens);
			free_string_arr(minishell->tokens);
			free_string_arr(minishell->env_char);
		}
		else
			printf("Chakerty bacvel e u chi pakvel kam verjin simvoly '\\' e:\n");
		free(minishell->str);
	}
	delete_tokens(tokens);
	free_string_arr(minishell->tokens);
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
	free(arr);
	printf("--------------------------------------------------\n");
}
