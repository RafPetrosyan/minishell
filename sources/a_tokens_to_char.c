#include "minishell.h"

void	free_string_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr == 0)
		return ;
	while (arr[i] != 0)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}
