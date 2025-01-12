#include <minishell.h>

int	check_n_flag(char **arr, int *i)
{
	int	j;
	int	flag;

	flag = 1;
	while (arr[*i] != 0)
	{
		j = 0;
		if (arr[*i][j] == '-')
		{
			++j;
			while (arr[*i][j] == 'n')
				++j;
			if (arr[*i][j] == '\0')
			{
				++(*i);
				flag = 0;
			}
			else
				return (flag);
		}
		else
			return (flag);
	}
	return (flag);
}

int	ft_echo(char **arr, int flag, int i, int j)
{
	if (arr[i] == 0)
	{
		write(1, "\n", 1);
		g_exit_status = 0;
		return (0);
	}
	flag = check_n_flag(arr, &i);
	while (arr[i] != 0)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			write(1, &arr[i][j], 1);
			++j;
		}
		if (arr[i + 1] == 0)
			break ;
		if (arr[i + 1] != 0)
			write(1, " ", 1);
		++i;
	}
	if (flag == 1)
		write(1, "\n", 1);
	g_exit_status = 0;
	return (0);
}
