/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_libft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:21 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/16 16:50:22 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	int		n;
	char	*str;

	n = ft_strlen(s);
	str = (char *)malloc((n + 1) * sizeof(char));
	if (str == 0)
		return (0);
	str[n--] = '\0';
	while (n >= 0)
	{
		str[n] = s[n];
		--n;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * (sizeof(char)));
	if (str == 0)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}
// poxvac e vor s1-y free ani

char	*ft_strjoin_free1(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * (sizeof(char)));
	if (str == 0)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	str[i++] = c;
	free(s1);
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}

void	*ft_calloc(size_t memb, size_t size)
{
	size_t	i;
	char	*str;

	if (memb > 0 && size > 0 && (4294967295 / memb < size))
		return (0);
	str = (char *)(malloc(memb * size));
	if (str == 0)
		return (0);
	i = 0;
	while (i < memb * size)
		str[i++] = 0;
	return ((void *)str);
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
