/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:54 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:55 by rafpetro         ###   ########.fr       */
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

int	write_tokens(int *i, t_tokens **arr, int arr_i, t_minishell *minishell)
{
	int	j;
	int count;
	char *str;

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
			count += write_non_quote(str, i, arr[arr_i], &j, minishell);
			if (str[*i - 1] == '|' || str[*i - 1] == '<' || str[*i - 1] == '>')
			{
				arr[arr_i]->str[j] = '\0';
				return (count);
			}
		}
		if (str[*i] == ' ' || str[*i] == '|' || str[*i] == '<' || str[*i] =='>')
			break ;
	}
	arr[arr_i]->str[j] = '\0';
	return (count);
}

int	set_type(char *str, int *i, t_tokens *token)
{
	if (str[*i] == '|')
		return(token->type = 1);
	else if (str[(*i)] == '<' && str[(*i) + 1] != '<')
		return(token->type = 2);
	else if (str[*i] == '>' && str[*i + 1] != '>')
		return(token->type = 3);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		return(token->type = 4);
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return(token->type = 5);
	return (0);
}

int	write_non_quote(char *str, int *i, t_tokens *token, int *j , t_minishell *minishell)
{
	int k;
	int count;

	k = *i;
	count = 0;
	while (str[*i] != '\0')
	{  
		if (str[*i] == '$')
			count += write_dollar(i, token->str, minishell, j, minishell->str);
		else if (check_operator(str, &k) != 0)
		{
			if (set_type(str, i, token) == PIPE)
				++minishell->pipe_count;
			if (set_type(str, i, token) == HERE_DOCK)
				++minishell->here_doc_count;
			count += write_operator(str, i, token, j);
			return (count);
		}
		else
		{
			token->str[*j] = str[*i];
			++count;
			++(*i);
			++(*j);
		}
		if (str[*i] == ' ' || str[*i] == '\'' || str[*i] == '"' || str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
			return (count);
	}
	return (count);
}

int write_one_quote(char *str, int *i, t_tokens *token, int *j)
{
	int flag;
	int count;

	flag = 0;
	count = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
		{
			++flag;
			++(*i);
			continue;
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


int write_two_quote(int *i, t_tokens *token, int *j, t_minishell *minishell)
{
	int flag;
	int count;
	char *str;

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
			continue;
		}
		if (str[*i] == '$')
			count += write_dollar_quote(i, token->str, minishell, j);
		else
		{
			token->str[*j] = str[*i];
			++count;
			++(*j);
			++(*i);
		}
	}
	return (count);
}
