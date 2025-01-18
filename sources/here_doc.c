/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:42 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/17 15:42:19 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_malloc_error(t_minishell *minishell)
{
	ft_printf("Memmory error!!\n");
	free_memory(minishell, 1);
	exit(55);
}

void	print_inputs(int fd, t_minishell *minishell)
{
	int		index;
	int		index_cpy;
	char	*str;

	index = 0;
	while (minishell->here_doc_str[index] != 0)
	{
		if (minishell->here_doc_str[index] == '$')
		{
			index_cpy = index;
			str = malloc((dollar_arg_len(minishell->here_doc_str,
							&index_cpy, minishell) + 1) * sizeof(char));
			if (str == 0)
				free_malloc_error(minishell);
			index_cpy = 0;
			write_dollar(&index, str, minishell, &index_cpy);
			write(fd, str, index_cpy);
			free(str);
			continue ;
		}
		write(fd, &minishell->here_doc_str[index], 1);
		++index;
	}
	write(fd, "\n", 1);
}

void	here_doc_run_helper2(int fd, t_minishell *minishell)
{
	print_inputs(fd, minishell);
	free(minishell->here_doc_str);
	minishell->here_doc_str = 0;
}

int	here_doc_run_helper1(char *str, int fd, t_minishell *minishell, char *stop)
{
	while (str != 0)
	{
		str = readline("> ");
		if (str == 0)
		{
			printf("mini: warning: here-document\
 at line X delimited by end-of-file (wanted `%s')\n", stop);
			here_doc_run_helper2(fd, minishell);
			break ;
		}
		if (ft_strcmp(str, stop) != 0)
		{
			minishell->here_doc_str = ft_strjoin_free1(minishell->here_doc_str,
					str, '\n');
			free(str);
		}
		else
		{
			free(str);
			here_doc_run_helper2(fd, minishell);
			break ;
		}
	}
}

void	her_doc_run(char *stop, int fd, t_minishell *minishell)
{
	char	*str;

	str = "";
	minishell->here_doc_str = readline("> ");
	if (minishell->here_doc_str == 0)
	{
		printf("mini: warning: here-document at\
 line X delimited by end-of-file (wanted `%s')\n", stop);
		return ;
	}
	if (ft_strcmp(minishell->here_doc_str, stop) == 0)
	{
		free(minishell->here_doc_str);
		minishell->here_doc_str = 0;
		return ;
	}
	here_doc_run_helper1(str, fd, minishell, stop);
}

int	check_syntax_helper(t_tokens **tokens, int *i)
{
	while (tokens[*i] != 0)
	{
		if (i == 0 && tokens[0]->type == PIPE)
		{
			g_exit_status = 2;
			ft_printf("bash: syntax error near\
 unexpected token `%s'", tokens[*i]->str);
			return (2);
		}
		if ((tokens[*i]->type == IN_REDIR || tokens[*i]->type == OUT_REDIR
				|| tokens[*i]->type == OUT_APPEND_REDIR
				|| tokens[*i]->type == HERE_DOCK)
			&& (tokens[*i + 1] != 0 && tokens[*i + 1]->type != 0))
		{
			g_exit_status = 2;
			ft_printf("bash: syntax error near\
 unexpected token `%s'", tokens[*i + 1]->str);
			return (2);
		}
		++(*i);
	}
	return (0);
}

int	check_syntax(t_tokens **tokens)
{
	int	i;

	i = 0;
	if (tokens[0] == 0)
		return (2);
	if (check_syntax_helper(tokens, &i) == 2)
		return (2);
	if (tokens[i - 1]->type != 0)
	{
		g_exit_status = 2;
		ft_printf("bash: syntax error near unexpected token `newline'");
		return (2);
	}
	g_exit_status = 0;
	return (0);
}
