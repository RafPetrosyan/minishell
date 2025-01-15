#include "../includes/minishell.h"
#include <unistd.h>

int	g_exit_status = 0;

void	set_default_values(t_minishell *minishell)
{
	minishell->str = "";
	minishell->env_list = 0;
	minishell->env_char = 0;
	minishell->tokens = 0;
	minishell->fd_arr = 0;
	minishell->doc_arr = 0;
	minishell->pipe_count = 0;
	minishell->here_doc_count = 0;
	minishell->cmd_arr = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	if (minishell == 0)
	{
		ft_printf("! Memmory alocation error !");
		exit(55);
	}
	set_default_values(minishell);
	minishell->env_list = env_to_list(env);
	anyndhat(minishell);
	free_memory(minishell, 1);
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
