/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:54 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/18 10:12:59 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_operator(char *str, int *i, t_tokens *token, int *j)
{
	int	count;

	count = 0;
	if (str[*i] == '|' && ++count)
		token->str[(*j)++] = str[(*i)++];
	else if (str[(*i)] == '<' && str[(*i) + 1] != '<' && ++count)
		token->str[(*j)++] = str[(*i)++];
	else if (str[*i] == '>' && str[*i + 1] != '>' && ++count)
		token->str[(*j)++] = str[(*i)++];
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		count += 2;
		token->str[(*j)++] = str[(*i)++];
		token->str[(*j)++] = str[(*i)++];
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		count += 2;
		token->str[(*j)++] = str[(*i)++];
		token->str[(*j)++] = str[(*i)++];
	}
	return (count);
}

int	write_token_helper(t_tokens **arr, int arr_i, int count, int j)
{
	arr[arr_i]->str[j] = '\0';
	return (count);
}

int	write_tokens(int *i, t_tokens **arr, int arr_i, t_minishell *minishell)
{
	int		j;
	int		count;
	char	*str;

	str = minishell->str;
	j = 0;
	count = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		++(*i);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
			count += write_one_quote(str, i, arr[arr_i], &j);
		else if (str[*i] == '"')
			count += write_two_quote(i, arr[arr_i], &j, minishell);
		else
		{
			count += write_non_quote(i, arr[arr_i], &j, minishell);
			if (str[*i - 1] == '|' || str[*i - 1] == '<' || str[*i - 1] == '>')
				return (write_token_helper(arr, arr_i, count, j));
		}
		if (str[*i] == 32 || str[*i] == '|' || str[*i] == 60 || str[*i] == '>')
			break ;
	}
	return (write_token_helper(arr, arr_i, count, j));
}

int	set_type(char *str, int *i, t_tokens *token)
{
	if (str[*i] == '|')
		return (token->type = PIPE);
	else if (str[(*i)] == '<' && str[(*i) + 1] != '<')
		return (token->type = IN_REDIR);
	else if (str[*i] == '>' && str[*i + 1] != '>')
		return (token->type = OUT_REDIR);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		return (token->type = HERE_DOCK);
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return (token->type = OUT_APPEND_REDIR);
	return (0);
}

int	write_two_quote_helper(t_tokens *token, int *j, int *i, char *str)
{
	token->str[*j] = str[*i];
	++(*j);
	++(*i);
	return (1);
}

void	stugel_avelacnel(char *str, int *i,
	t_minishell *minishell, t_tokens *token)
{
	if (set_type(str, i, token) == PIPE)
		++minishell->pipe_count;
	if (set_type(str, i, token) == HERE_DOCK)
		++minishell->here_doc_count;
}

int	write_non_quote_helper(char *str, int *i)
{
	if (str[*i] == ' ' || str[*i] == '\''
		|| str[*i] == '"' || str[*i] == '|'
		|| str[*i] == '<' || str[*i] == '>')
		return (1);
	return (0);
}

int	write_non_quote(int *i, t_tokens *token, int *j, t_minishell *minishell)
{
	int		k;
	int		count;
	char	*str;

	k = *i;
	count = 0;
	if (minishell->here_doc_str == 0)
		str = minishell->str;
	else
		str = minishell->here_doc_str;
	while (str[*i] != '\0')
	{
		if (str[*i] == '$')
			count += write_dollar(i, token->str, minishell, j);
		else if (check_operator(str, &k) != 0)
		{
			stugel_avelacnel(str, i, minishell, token);
			return (veragrel(&count, write_operator(str, i, token, j)));
		}
		else
			count += write_two_quote_helper(token, j, i, str);
		if (write_non_quote_helper(str, i))
			return (count);
	}
	return (count);
}

int	write_one_quote(char *str, int *i, t_tokens *token, int *j)
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
		{
			++flag;
			++(*i);
			if (flag == 1)
				continue ;
		}
		if (flag == 2)
			return (count);
		token->str[*j] = str[*i];
		++count;
		++(*i);
		++(*j);
	}
	return (count);
}

int	write_two_quote(int *i, t_tokens *token, int *j, t_minishell *minishell)
{
	int		flag;
	int		count;
	char	*str;

	str = minishell->str;
	flag = 0;
	count = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '"')
		{
			++(*i);
			++flag;
			if (flag == 2)
				return (count);
			continue ;
		}
		if (str[*i] == '$')
			count += write_dollar_quote(i, token->str, minishell, j);
		else
			count += write_two_quote_helper(token, j, i, str);
	}
	return (count);
}
