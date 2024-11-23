#include <minishell.h>

int	check_n_flag(t_tokens **tokens, int *i)
{
	int	j;
	int	flag;

	flag = 1;
	while (tokens[*i] != 0 && tokens[*i]->type == 0)
	{
		j = 0;
		if (tokens[*i]->str[j] == '-')
		{
			++j;
			while (tokens[*i]->str[j] == 'n')
				++j;
			if (tokens[*i]->str[j] == '\0')
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

int	ft_echo(t_tokens **tokens, int flag, int i, int j)
{
	if (tokens[i] == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	flag = check_n_flag(tokens, &i);
	while (tokens[i] != 0 && tokens[i]->type == 0)
	{
		j = 0;
		while (tokens[i]->str[j] != '\0')
		{
			write(1, &tokens[i]->str[j], 1);
			++j;
		}
		if (tokens[i + 1] == 0)
			break ;
		if (tokens[i + 1]->type == 0)
			write(1, " ", 1);
		++i;
	}
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}
