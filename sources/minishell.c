#include "../includes/minishell.h"
#include <unistd.h>

char g_exit_status = 0;

void	free_memory(t_minishell *minishell)
{
	delete_tokens(minishell->tokens);
	free_string_arr(minishell->env_char);
	delete_env_list(minishell->env_list);
	free(minishell->str);
	free(minishell);
	exit(1);
}

void	*ft_malloc(int count, int size, t_minishell *minishell)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (ptr == 0)
		free_memory(minishell);
	return (ptr);
}

void	setDefaultValues(t_minishell *minishell)
{
	minishell->env_list = 0;
	minishell->str = "";
	minishell->env_char = 0;
	minishell->tokens = 0;
	minishell->pipe_count = 0;
	minishell->here_doc_count = 0;
	minishell->fd_arr = 0;
	minishell->doc_arr = 0;
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
		perror("! Memmory alocation error !");
		exit(1);
	}
	setDefaultValues(minishell);
	minishell->env_list = env_to_list(env);
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
			minishell->here_doc_count = 0;
			minishell->cmd_arr = 0;
			minishell->tokens = split_tokens(0, minishell->str, minishell);
			if (check_syntax(minishell->tokens) == 2)// memmory xndir klini ete zut continue toghnem
				continue;
			minishell->fd_arr = malloc((minishell->pipe_count) * sizeof(int *));
			if (minishell->pipe_count != 0 && minishell->fd_arr == 0)
			{
				printf("Memmory error!!!!!");
				return(1);
			}
			for (int i = 0; i < minishell->pipe_count; i++)
				minishell->fd_arr[i] = malloc(2 * sizeof(int));
			minishell->doc_arr = malloc((minishell->here_doc_count) * sizeof(int *));
			if (minishell->here_doc_count!=0 && minishell->doc_arr == 0)
			{
				printf("Memmory error!!!!!");
				return(1);
			}
			for (int i = 0; i < minishell->here_doc_count; i++)
				minishell->doc_arr[i] = malloc(2 * sizeof(int));
			minishell->env_char = env_to_char(minishell->env_list);
			here_docs_init(minishell);
			if (minishell->pipe_count == 0 && cmds(minishell->tokens, minishell, -1) == 2)
				break ;
			else if (minishell->pipe_count != 0)
			{
				pipe_commands_init(minishell, minishell->tokens);
			}
			delete_tokens(minishell->tokens);
			free_string_arr(minishell->env_char);
			free(minishell->cmd_arr);
			minishell->cmd_arr = 0;
		}
		else
			printf("Chakerty bacvel e u chi pakvel kam verjin simvoly '\\' e:\n");
		free(minishell->str);
		if (minishell->pipe_count != 0 && minishell->fd_arr != 0)
		{
			for (int i = 0; i < minishell->pipe_count; i++)
				free(minishell->fd_arr[i]);
		}
		free(minishell->fd_arr);
		minishell->fd_arr = 0;
		if (minishell->here_doc_count !=0 && minishell->doc_arr != 0)
		{
			for (int i = 0; i < minishell->here_doc_count; i++)
				free(minishell->doc_arr[i]);
		}
		free(minishell->doc_arr);
		minishell->doc_arr = 0;
	}
	
	if (minishell->pipe_count != 0 && minishell->fd_arr != 0)
	{
		for (int i = 0; i < minishell->pipe_count; i++)
			free(minishell->fd_arr[i]);
	}
	if (minishell->here_doc_count !=0 && minishell->doc_arr != 0)
	{
		for (int i = 0; i < minishell->here_doc_count; i++)
			free(minishell->doc_arr[i]);
	}
	free(minishell->fd_arr);
	free(minishell->doc_arr);
	free(minishell->cmd_arr);
	delete_tokens(minishell->tokens);
	free_string_arr(minishell->env_char);
	delete_env_list(minishell->env_list);
	free(minishell->str);
	free(minishell);
	return (g_exit_status);
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
