/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:36 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:37 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_int_to_arr(char *str, int nmb, int *index)
{
	int	temp;
	int	digits;
	int	i;

	temp = nmb;
	digits = 0;
	if (temp == 0)
		digits = 1;
	else
	{
		while (temp != 0)
		{
			temp /= 10;
			digits++;
		}
	}
	str[digits] = '\0';
	i = digits - 1;
	while (i >= 0)
	{
		str[i] = (nmb % 10) + '0';
		nmb /= 10;
		--i;
	}
	(*index) += digits;
}

size_t	ft_strlcpy(char *dst, char *src, size_t size, int *j)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[(*j)++] = src[i];
		++i;
	}
	return (ft_strlen(src));
}
int	check_env_key(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	find_to_env(char *str, int *i, t_EnvList *env)
{
	int	j;

	while (env != 0)
	{
		j = 0;
		while (env->key[j] == str[*i + j])
		{
			if (env->key[j + 1] == '\0' && !(check_env_key(str[*i + j + 1])))
			{
				*i += j + 1;
				return (ft_strlen(env->value));
			}
			++j;
		}
		env = env->next;
	}
	while (check_env_key(str[*i]))
		++(*i);
	return (0);
}

int	dollar_arg_len(char *str, int *index, t_minishell *minishell)
{
	++(*index);
	if (str[*index] == '?')
	{
		++(*index);
		if (g_exit_status >= 0 && g_exit_status <= 9)
			return (1);
		if (g_exit_status >= 10 && g_exit_status <= 99)
			return (2);
		if (g_exit_status >= 100)
			return (3);
	}
	if (str[*index] == '\0' || str[*index] == '\\' || str[*index] == ' ')
		return (1);
	if (str[*index] == '0' && ++(*index))
		return (4);
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (0);
	if (str[*index] == '\'' || str[*index] == '"')
		return (0);
	return (find_to_env(str, index, minishell->env_list));
}

int	dollar_arg_len_quote(int *index, t_minishell *minishell)
{
	char	*str;

	str = minishell->str;
	++(*index);
	if (str[*index] == '?')
	{
		++(*index);
		if (g_exit_status >= 0 && g_exit_status <= 9)
			return (1);
		if (g_exit_status >= 10 && g_exit_status <= 99)
			return (2);
		if (g_exit_status >= 100)
			return (3);
	}
	if (str[*index] == '\0' || str[*index] == '\\' || str[*index] == ' '
		|| str[*index] == '\'' || str[*index] == '"')
		return (1);
	if (str[*index] == '0' && ++(*index))
		return (4);
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (0);
	return (find_to_env(str, index, minishell->env_list));
}

int	write_dollar(int *index, char *token_str, t_minishell *minishell, int *j, char *str)
{
	int		count;

	count = 0;
	++(*index);
	if (str[*index] == '\0' || (str[*index] == '\\' || str[*index] == ' '))
	{
		token_str[(*j)++] = '$';
		++count;
		return (count);
	}
	if (str[*index] == '?' && ++(*index))
	{
		write_int_to_arr(&token_str[*j], g_exit_status, j);
		return (1);
	}
	if (str[*index] == '0' && ++(*index))
	{
		ft_strlcpy(token_str + *j, "bash", 5, j);
		count += 4;
		return (count);
	}
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (count);
	if (str[*index] == '\'' || str[*index] == '"')
		return (count);
	count += find_to_env_write(str, index, minishell->env_list, token_str, j);
	return (count);
}

int	write_dollar_quote(int *index, char *token_str, t_minishell *shell, int *j)
{
	int		count;
	char	*str;

	count = 0;
	str = shell->str;
	++(*index);
	if (str[*index] == '\0' || (str[*index] == '\\' || str[*index] == ' '
			|| str[*index] == '\'' || str[*index] == '"'))
	{
		token_str[(*j)++] = '$';
		++count;
		return (count);
	}
	if (str[*index] == '?' && ++(*index))
	{
		token_str[(*j)] = '0';
		++(*j);
		return (1);
	}
	if (str[*index] == '0' && ++(*index))
	{
		ft_strlcpy(token_str + *j, "bash", 5, j);
		count += 4;
		return (count);
	}
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (count);
	if (str[*index] == '\'' || str[*index] == '"')
		return (count);
	count += find_to_env_write(str, index, shell->env_list, token_str, j);
	return (count);
}

int	find_to_env_write(char *str, int *i, t_EnvList *env, char *token_str, int *k)
{
	int j;
	int count;

	count = 0;
	while (env != 0)
	{
		j = 0;
		while (env->key[j] == str[*i + j])
		{
			if (env->key[j + 1] == '\0' && !(check_env_key(str[*i + j + 1])))
			{
				ft_strlcpy(token_str, env->value, ft_strlen(env->value) + 1, k);
				*i += j + 1;
				count += ft_strlen(env->value);
				return (count);
			}
			++j;
		}
		env = env->next;
	}
	while (check_env_key(str[*i]))
		++(*i);
	return (count);
}
