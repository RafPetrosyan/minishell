#include "../includes/minishell.h"

int	check_quote(t_minishell *minishell)
{
	int	i;
	int	lenght;

	i = 0;
	lenght = ft_strlen(minishell->str);
	if (lenght != 0 && minishell->str[lenght - 1] == '\\')
		return (0);
	while (i < lenght)
	{
		if (minishell->str[i] == '\'')
		{
			if (check_one_quote(minishell->str, &i) == -1)
				return (0);
		}
		else if (minishell->str[i] == '"')
		{
			if (check_two_quote(&i, minishell) == -1)
				return (0);
		}
		else
			++i;
	}
	return (1);//ok
}

int	check_non_quote(int *i, t_minishell *minishell)
{
	int	count;
	int	operator;
	char	*str;

	count = 0;
	str = minishell->str;
	while (str[*i] != '\0')
	{
		if (str[*i] == '$')
			count += dollar_arg_len(str, i, minishell);
		else if (operator = check_operator(str, i, minishell))
			return (operator);
		else
		{
			++count;
			++(*i);
		}
		if (str[*i] == ' ' || str[*i] == '\0' || str[*i] == '\''
			|| str[*i] == '"' || str[*i] == '|'
			|| str[*i] == '<' || str[*i] == '>')
			return (count);
	}
	return (count);
}

int	check_one_quote(char *str, int *i)
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
			++flag;
		++(*i);
		++count;
		if (flag == 2)
			return (count - 2);//pakvel e
	}
	printf("chi pakvel meky");
	return (-1);// chi pakvel 
}

int	check_two_quote(int *i, t_minishell *minishell)
{
	int	flag;
	int	count;

	count = 0;
	flag = 0;
	while (minishell->str[*i] != '\0')
	{
		if (minishell->str[*i] == '"')
		{
			++flag;
			++(*i);
			++count;
		}
		else if (minishell->str[*i] == '$')
			count += dollar_arg_len_quote(i, minishell);// --(*i)
		else
		{
			++count;
			++(*i);
		}
		if (flag == 2)
			return (count - 2);//pakvel e
	}
	return (-1);// chi pakvel 
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == 0)
	{
		return (0);
	}
	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}
