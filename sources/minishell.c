#include "minishell.h"

int main()
{
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
		//printf("%s\n", str);
		if (check_quote(str) == 1)
		{
			// printf("Hello\n");
			arr = malloc_word_len_arr(str);
		}
		else
		{
			while(arr[i] != -1)
				printf("%d\n", arr[i++]);
		}
		free(str);
	}
	return (0);
}