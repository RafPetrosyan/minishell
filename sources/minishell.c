#include "../includes/minishell.h"
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_tokens **tokens;
	char	*str;

	(void)argc;
	(void)argv;
	str = "";
	minishell = malloc(sizeof(t_minishell));
	minishell->env_list = env_to_list(env);
	while (str)
	{
		str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		if (!str)
			return (0);
		if (str[0] != '\0')  // inchqan space ka ancnem ete datark eghav chavelacnem
			add_history(str);
		if (check_quote(str, minishell) == 1)
		{
			tokens = split_tokens(str, 0, minishell);
			print_tokens_info(str, minishell, tokens);
			builtins(tokens, minishell);
		}
		else
			printf("Chakerty bacvel e u chi pakvel kam verjin simvoly '\\' e:\n");
		free(str);
	}
	delete_env_list(minishell->env_list);
	return (0);
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
