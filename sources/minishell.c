#include "minishell.h"
#include <unistd.h>

int main()
{
	t_tokens **tokens;
	char	*str;
	int *arr;
	int i=0;
	str = "";
	while (str)
	{
		i = 0;
		str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		if (!str)
			return (0);
		add_history(str);
		if (check_quote(str) == 1)
		{
			arr = malloc_word_len_arr(str);
			while(arr[i] != -1)
				printf("%d\n", arr[i++]);
			tokens = split_tokens(str, 0);
			i = 0;
			while (tokens[i] != 0)
			{
				printf("%s\t", tokens[i]->str);
				++i;
			}
		}
		free(str);
	}
	return (0);
}