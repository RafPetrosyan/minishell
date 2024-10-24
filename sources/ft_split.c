#include "minishell.h"

int	ft_get_word_count(char *str, char c)
{
	int	i;
	int	word_count;
    int flag1;
    int flag2;

    flag1 = 0;
    flag2 = 0;
	word_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((i == 0 && str[i] != c) || (i != 0
				&& str[i] != c && str[i - 1] == c && ((flag1 % 2 == 0) && (flag2 % 2 == 0))))
			++word_count;
        if (str[i] == '\'' && flag2 % 2 == 0)
            ++flag1;
        if (str[i] == '"' && flag1 % 2 == 0 && check_zuyg_slash(str, i) == 0)
            ++flag2;
		++i;
	}
	return (word_count);
}

static int	ft_word_mall(char *str, int word_count, char c, char **arr)
{
	int	i;
	int	arr_index;
	int	word_len;

	arr_index = 0;
	word_len = 0;
	i = 0;
	while (str[i] != '\0' && arr_index < word_count)
	{
		while (str[i] == c)
			++i;
		while (str[i] != c && str[i] != '\0')
		{
			++word_len;
			++i;
		}
		arr[arr_index] = (char *)malloc((word_len + 1) * sizeof(char));
		if (arr[arr_index] == 0)
			return (-1);
		word_len = 0;
		++arr_index;
	}
	return (0);
}

static void	ft_write_word(char *str, int word_count, char c, char **arr)
{
	int	i;
	int	arr_index;
	int	word_len;

	i = 0;
	arr_index = 0;
	while (str[i] != '\0' && arr_index < word_count)
	{
		word_len = 0;
		while (str[i] == c)
			++i;
		while (str[i] != c && str[i] != '\0')
		{
			arr[arr_index][word_len] = str[i];
			++word_len;
			++i;
		}
		arr[arr_index][word_len] = '\0';
		++arr_index;
	}
}

char	**ft_split(char *str, char c)
{
	int		word_count;
	char	**arr;

	if (str == 0)
		return (0);
	word_count = ft_get_word_count(str, c);
	arr = (char **)malloc((word_count + 1) * sizeof(char *));
	if (arr == 0)
		return (0);
	if (ft_word_mall(str, word_count, c, arr) == -1)
    {
        word_count = 0; // word count vorpes index ogtagorcel
        while (arr[word_count] != 0)
            free(arr[word_count++]);
        free(arr);
		return (0);
    }
	ft_write_word(str, word_count, c, arr);
	arr[word_count] = 0;
	return (arr);
}
