#include "minishell.h"

int	ft_get_word_len(char *str, int *i)
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
			count += (check_two_quote(str, i));
		else
			count += check_non_quote(str, i);
		if (str[*i] == ' ')
			return (count);
	}
	return (count);
}

int	*malloc_word_len_arr(char *str)
{
	int *arr;
	int count;
	int	i;
	int arr_i;

	i = 0;
	arr_i = 0;
	count = ft_get_word_count(str);//, ' ');
	arr = malloc((count + 1) * sizeof(int));
	if (arr == 0)
		return (0);//!printf("Memory allocation error !"));// azatel hishoghutyuny
	while (arr_i < count)
	{
		arr[arr_i] = ft_get_word_len(str, &i);
		++arr_i;
	}
	arr[count] = -1;
	return (arr);
}

int	ft_get_word_count(char *str)//, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_get_word_len(str, &i) != 0)
		++count;
	return (count);
}

// char **split_tokens(char *str)
// {
// 	t_tokens	**arr;
// 	int	*len_arr;
// 	int	tokens_count;
// 	int	i;

// 	tokens_count = ft_get_word_count(str);
// 	len_arr = malloc_word_len_arr(str);
// 	i = 0;
// 	arr = malloc((tokens_count + 1) * sizeof(t_tokens *));
// 	while (i < tokens_count)
// 	{
// 		arr[i]->str = malloc(len_arr[i] * sizeof(char));
// 		if (arr[i]->str == 0)
// 			return (0);
// 		// write_tokens && tokenization function
// 		++i;
// 	}
// 	return (arr);
// }
// void	write_tokens(char *str, int i, t_tokens **arr, int arr_i)
// {

// }

int	dollar_arg_len(char *str, int index)
{
	int index_2;
	int	count;

	index_2 = index;
	count = 0;
	while (str[index] != '\\' && str[index] != '"' && str[index] != ' ')
	{
		++count;
		++index;
	}
	return (count);
}
