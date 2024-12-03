#include "minishell.h"

int	check_operator(char *str, int *i, t_minishell *minishell)
{
	if (str[*i] == '|' && ++(*i))
		return (1);
	else if (str[*i] == '<' && str[*i + 1] != '<' && ++(*i))
		return (1);
	else if (str[*i] == '>' && str[*i + 1] != '>' && ++(*i))
		return (1);
	else if (str[*i] == '<' && str[*i + 1] == '<' && ((*i) += 2))
		return (2);
	else if (str[*i] == '>' && str[*i + 1] == '>' && ((*i) += 2))
		return (2);
	return (0);
}

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
			count += (check_two_quote(i, minishell));
		else
			count += check_non_quote(i, minishell);
		if (str[*i] == ' ' || str[*i] == '|'
			|| str[*i] == '<' || str[*i] == '>')
			return (count);
		if (str[*i - 1] == '|' || str[*i - 1] == '<'
			|| str[*i - 1] == '>')
			return (count);
	}
	return (count);
}

int	*malloc_word_len_arr(char *str, t_minishell *minishell)
{
	int	*arr;
	int	count;
	int	i;
	int	arr_i;
	int	word_len;

	i = 0;
	arr_i = 0;
	count = ft_get_word_count(str, minishell);
	arr = malloc((count + 1) * sizeof(int));
	if (arr == 0)
		return (0);
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
	int	len;

	i = 0;
	count = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (ft_get_word_len(str, &i, minishell) != 0)
			++count;
	}
	return (count);
}

t_tokens	**split_tokens(int i, t_minishell *minishell)
{
	t_tokens	**arr;
	int			*len_arr;
	int			tokens_count;
	int			arr_i;
	char		*str;

	str = minishell->str;
	tokens_count = ft_get_word_count(str, minishell);
	len_arr = malloc_word_len_arr(str, minishell);
	arr_i = 0;
	arr = (t_tokens **)malloc((tokens_count + 1) * sizeof(t_tokens *));
	if (arr == 0)
		return (0);
	while (arr_i < tokens_count)
		arr[arr_i++] = malloc(sizeof(t_tokens));
	arr_i = 0;
	while (arr_i < tokens_count)
	{
		arr[arr_i]->type = 0;
		arr[arr_i]->str = malloc((len_arr[arr_i] + 1) * sizeof(char));
		if (arr[arr_i]->str == 0)
			return (0);
		if (write_tokens(str, &i, arr, arr_i, minishell) != 0)
			++arr_i;
	}
	arr[tokens_count] = 0;
	free(len_arr);
	return (arr);
}
