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