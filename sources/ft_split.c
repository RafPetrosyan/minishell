#include "minishell.h"

int	ft_get_word_len(char *str, int *i, t_minishell *minishell)
{
	int	count;

	count = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		++(*i);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
			count += (check_one_quote(str, i));
		else if (str[*i] == '"')
			count += (check_two_quote(str, i, minishell));
		else
			count += check_non_quote(str, i, minishell);
		if (str[*i] == ' ')
			return (count);
	}
	return (count);
}

int	*malloc_word_len_arr(char *str, t_minishell *minishell)
{
	int *arr;
	int count;
	int	i;
	int arr_i;
	int	word_len;

	i = 0;
	arr_i = 0;
	count = ft_get_word_count(str, minishell);
	arr = malloc((count + 1) * sizeof(int));
	if (arr == 0)
		return (0);//!printf("Memory allocation error !"));// azatel hishoghutyuny
	while (arr_i < count)
	{
		word_len = ft_get_word_len(str, &i, minishell);
		if (word_len != 0)
			arr[arr_i++] = word_len;
	}
	arr[count] = -1;
	return (arr);
}

int	ft_get_word_count(char *str, t_minishell *minishell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (ft_get_word_len(str, &i, minishell) != 0)
			++count;
	}
	return (count);
}

t_tokens **split_tokens(char *str, int i, t_minishell *minishell)
{
	t_tokens	**arr;
	int	*len_arr;
	int	tokens_count;
	int	arr_i;

	tokens_count = ft_get_word_count(str, minishell);
	len_arr = malloc_word_len_arr(str, minishell);
	arr_i = 0;
	printf("tokens count: %d\n", tokens_count);
	arr = (t_tokens**)malloc((tokens_count + 1) * sizeof(t_tokens *));
	if (arr == 0)
		return (0);
	while (arr_i < tokens_count)
		arr[arr_i++] = malloc(sizeof(t_tokens));
	arr_i = 0;
	while (arr_i < tokens_count)
	{
		arr[arr_i]->str = malloc((len_arr[arr_i] + 1) * sizeof(char));
		if (arr[arr_i]->str == 0)
			return (0);
		write_tokens(str, &i, arr, arr_i, minishell);
		++arr_i;
	}
	arr[tokens_count] = 0;
	free(len_arr);
	return (arr);
}


