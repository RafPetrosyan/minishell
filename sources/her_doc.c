/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:42 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:43 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_inputs(char *lines, int fd, t_minishell *minishell)
{
	int		index;
	int		index_cpy;
	char	*str;

	index = 0;
	while (lines[index] != 0)
	{
		if (lines[index] == '$')
		{
			index_cpy = index;
			str = malloc((dollar_arg_len(lines, &index_cpy, minishell) + 1) * sizeof(char));
			if (str == 0)
			{
				ft_printf("Memmory erroe!!");
				exit(2);
			}
			index_cpy=0;
			write_dollar(&index, str, minishell, &index_cpy, lines);
			write(fd, str, index_cpy);
			free(str);
			continue;
		}
		write(fd, &lines[index], 1);
		++index;
	}
	write(fd, "\n", 1);
}

void	her_doc(char *stop, int fd, t_minishell* minishell)
{
	char	*str;
	char	*lines;

	str = "";
	lines = readline("> ");
	if (lines == 0)
		return;
	if (ft_strcmp(lines, stop) == 0)
	{
		free(lines);
		return;
	}
	while (str != 0)
	{
		str = readline("> ");
		if (str == 0)
		{
			write(2,"Memmory error !!!!\n", 19);
			free(lines);
			// exit
			return ;
		}
		if (ft_strcmp(str, stop) != 0)
		{
			lines = ft_strjoin_free1(lines, str, '\n');
			free(str);
		}
		else
		{
			print_inputs(lines, fd, minishell);
			free(str);
			free(lines);
			break;
		}
	}
}
int check_syntax(t_tokens **tokens)
{
	int	i;

	i = 0;
	if (tokens[0] == 0)
		return 2;
	while (tokens[i] != 0)
	{
		if (i == 0 && tokens[0]->type == PIPE)
		{
			g_exit_status = 2;
			ft_printf("bash: syntax error near unexpected token `%s'", tokens[i]->str);
			return 2;
		}
		if ((tokens[i]->type == IN_REDIR || tokens[i]->type == OUT_REDIR || tokens[i]->type == OUT_APPEND_REDIR || tokens[i]->type == HERE_DOCK) && (tokens[i + 1] != 0 && tokens[i + 1]->type != 0))
		{
			g_exit_status = 2;
			ft_printf("bash: syntax error near unexpected token `%s'", tokens[i + 1]->str);
			return 2;
		}
		++i;
	}
	if(tokens[i - 1]->type != 0)
	{
		g_exit_status = 2;
		ft_printf("bash: syntax error near unexpected token `newline'");
			return 2;
	}
	g_exit_status = 0;
	return (0);
}

