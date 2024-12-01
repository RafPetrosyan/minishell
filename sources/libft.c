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
	str[i++] = '/';
	free(s1);
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}
