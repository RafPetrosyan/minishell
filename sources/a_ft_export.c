/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:08 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:09 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_key_std(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')))
		return (1);
	++i;
	while (str[i] != '=' && str[i] != '\0' && (str[i] == '_'
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')))
		++i;
	if (str[i] == 0 || str[i] == '=')
		return (0);
	return (1);
}

int	ft_export(t_EnvList *env, char **tokens, int i, int j)
{
	t_EnvList	*export_node;

	if (tokens[1] == 0)
	{
		print_export(env, 0);
		g_exit_status = 0;
		return (0);
	}
	while (tokens[i] != 0)
	{
		if (check_key_std(tokens[i]) == 1)
		{
			write(2, " not a valid identifier", 23);
			g_exit_status = 1;
			++i;
			continue ;
		}
		g_exit_status = 0;
		ft_export_helper(tokens[i], env);
		export_node = find_to_env_export(tokens[i], env, &j);
		export_node->type = 0;
		++i;
	}
	return (0);
}

int	ft_export_helper(char *str, t_EnvList *env)
{
	t_EnvList	*export_node;
	int			j;

	j = 0;
	export_node = find_to_env_export(str, env, &j);
	if (export_node != 0)
	{
		if (str[j] == '=')
		{
			if (export_node->value != 0)
				free(export_node->value);
			export_node->value = ft_strdup(&(str[j + 1]));
		}
	}
	else
	{
		while (env->next != 0)
			env = env->next;
		env->next = add_list(str, 0, 0, 0);
	}
	return (0);
}

t_EnvList	*find_to_env_export(char *str, t_EnvList *env, int *i)
{
	int	j;

	while (env != 0)
	{
		j = 0;
		while (env->key[j] == str[j])
		{
			if (env->key[j + 1] == '\0'
				&& (str[j + 1] == '\0' || str[j + 1] == '=' ))
			{
				++j;
				*i += j;
				return (env);
			}
			++j;
		}
		env = env->next;
	}
	return (0);
}
